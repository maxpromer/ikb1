#ifndef __iKB_1_CPP__
#define __iKB_1_CPP__

#include "iKB_1.h"

iKB_1::iKB_1(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = 40; // Not not use
}

void iKB_1::init(void) {
	// clear initialized flag
	initialized = false;
	
	// Start initialized
	state = s_detect;
	
	// Set clock
	i2c_setClock(IKB_1_I2C_CLOCK);
	
	// Set buffer to old data
	dataBuffer.old = true;
	
	// clear queue
	iKB_1_qWrite.front = -1;
	iKB_1_qWrite.rear  = -1;
	iKB_1_qWrite.count = 0;
	
	// clear queue (2)
	iKB_1_qSerailRead.front = -1;
	iKB_1_qSerailRead.rear  = -1;
	iKB_1_qSerailRead.count = 0;
}

int iKB_1::prop_count(void) {
	// not supported
	return 0;
}

bool iKB_1::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool iKB_1::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool iKB_1::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool iKB_1::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool iKB_1::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

// Start here
void iKB_1::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// clear error flag
				error = false;
				// set initialized flag
				initialized = true;
				
				// Send reset module
				reset(false); // No sync !
				
				// Go to main state
				state = s_runing;
			} else {
				state = s_error;
			}
			break;
		
		case s_runing: {
			/*
			char str[20];
			sprintf(str, "C: %d\n", iKB_1_qWrite.count);
			uart_write_bytes(UART_NUM_0, str, strlen(str));
			*/
			uint8_t dataBlock[2];
			while(iKB_1_qWrite.count) { // loop all data in queue
				iKB_1_CommandData data = iKB_1_Dequeue(&iKB_1_qWrite);
				dataBlock[0] = data.command;
				dataBlock[1] = data.parameter;
				if (i2c->write(channel, address, dataBlock, 2) != ESP_OK) {
					errCount++;
					if (errCount > 10) {
						errCount = 0;
						state = s_error;
					}
					break;
				}
			}
			if (state == s_error) {
				break;
			}
		
			if (dataBuffer.old) { // if old data
				break; // not do things
			}
			
			// if new data
			if (i2c->write(channel, address, dataBuffer.write.data.block, dataBuffer.write.length) != ESP_OK) {
				errCount++;
				if (errCount > 10) {
					errCount = 0;
					state = s_error;
				}
				break;
			}
			
			if (dataBuffer.read.length <= 0) { // if not request data
				dataBuffer.old = true;
				break;  // not do more
			}
			
			// vTaskDelay(10 / portTICK_RATE_MS);
			
			// If a lot of data, Change speed of i2c
			bool i2cSpeedChange = dataBuffer.read.length > 3;
			if (i2cSpeedChange) {
				i2c_setClock(10E3); // Set to 10kHz
			}
			
			// Send request data
			uint8_t *pointer = 0;
			if (i2c->read(channel, address, pointer, 0, dataBuffer.read.data.block, dataBuffer.read.length) != ESP_OK) {
				errCount++;
				if (errCount > 10) {
					errCount = 0;
					state = s_error;
				}
				break;
			}
			
			// Set speed to default
			if (i2cSpeedChange) {
				i2c_setClock(IKB_1_I2C_CLOCK);
			}
			
			// Set it to old data
			dataBuffer.old = true;
			
		}
		
		case s_wait:
			if (error) {
				// wait polling_ms timeout
				if (is_tickcnt_elapsed(this->tickcnt, this->polling_ms)) {
					state = s_detect;
				}
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

	}
}

// Method
void iKB_1::i2c_setClock(uint32_t clock) {
	// Reset speed of I2C
	i2c_config_t conf;

	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = CHAIN_SDA_GPIO;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_io_num = CHAIN_SCL_GPIO;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = clock;

	i2c_param_config(I2C_NUM_1, &conf);
}

// Wait send data finish
bool iKB_1::sync_data(uint16_t wait_time) {
	uint16_t waiting_time = 0;
	while((!dataBuffer.old) && (waiting_time < wait_time)) { // loop if old flag not set and time for wait not more than 1s
		vTaskDelay(50 / portTICK_RATE_MS);
		waiting_time += 50;
	} 
	return waiting_time < wait_time;
}

// Send only, no parameter, no request
bool iKB_1::send(uint8_t command) {
	if (!sync_data()) {
		return false;
	}
	
	dataBuffer.write.data.command = command;
	dataBuffer.write.length = 1;
	dataBuffer.read.length = 0; // no request
	
	dataBuffer.old = false;
	
	return true;
}

// Send command and parameter, no request
bool iKB_1::send(uint8_t command, uint8_t parameter) {
	if (!sync_data()) {
		return false;
	}
	
	dataBuffer.write.data.command = command;
	dataBuffer.write.data.parameter = parameter;
	dataBuffer.write.length = 2;
	dataBuffer.read.length = 0; // no request
	
	dataBuffer.old = false;
	
	return true;
}

// Send command and parameter into circle queue
bool iKB_1::sendQ(uint8_t command, uint8_t parameter) {
	iKB_1_CommandData writeData;

	writeData.command = command;
	writeData.parameter = parameter;
	iKB_1_Enqueue(&iKB_1_qWrite, writeData);
	
	return true;
}

// Send command and parameter and request
bool iKB_1::send(uint8_t command, uint8_t parameter, int request_length) {
	if (!sync_data()) {
		return false;
	}
	
	dataBuffer.write.data.command = command;
	dataBuffer.write.data.parameter = parameter;
	dataBuffer.write.length = 2;
	dataBuffer.read.length = request_length;
	
	dataBuffer.old = false;
	
	return true;
}

// Send command and request, no parameter 
bool iKB_1::send(uint8_t command, int request_length) {
	if (!sync_data()) {
		return false;
	}
	
	dataBuffer.write.data.command = command;
	dataBuffer.write.length = 1;
	dataBuffer.read.length = request_length;
	
	dataBuffer.old = false;
	
	return true;
}

bool iKB_1::reset(bool sync = false) {
	if (!send((uint8_t)0x0)) {
		return false;
	}
	
	return sync ? sync_data() : true;
}

uint8_t iKB_1::digital_read(uint8_t ch, bool pullup) {
	// if (ch < 0 || ch > 7) { // warning: comparison is always false due to limited range of data type
	if (ch > 7) {
		return 0;
	}
	
	if (!send(0x08 + ch, (pullup ? 3 : 2), 1)) {
		return 0;
	}
	
	if (sync_data()) {
		return dataBuffer.read.data.block[0] != 0;
	} else {
		return 0;
	}
}

bool iKB_1::digital_write(uint8_t ch, uint8_t value) {
	// if (ch < 0 || ch > 7) { // warning: comparison is always false due to limited range of data type
	if (ch > 7) {
		return false;
	}
	
	/*
	send(0x08 + ch, (uint8_t)(value != 0 ? 1 : 0));
	
	return sync_data();
	*/
	
	sendQ(0x08 + ch, (uint8_t)(value != 0 ? 1 : 0));
	return true;
}

int iKB_1::analog_read(uint8_t ch) {
	// if (ch < 0 || ch > 7) { // warning: comparison is always false due to limited range of data type
	if (ch > 7) {
		return 0;
	}
	
	if (!send(0x80 + (ch << 4), (int)2)) {
		return false;
	}
	
	if (sync_data()) {
		return (dataBuffer.read.data.block[0]<<8)|dataBuffer.read.data.block[1];
	} else {
		return 0;
	}
}

bool iKB_1::motor(uint8_t ch, uint8_t dir, uint8_t speed) {
	if (ch < 1 || ch > 4) {
		return false;
	}
	speed = fmax(speed, 0);
	speed = fmin(speed, 100);
	
	char speed_t = 0;
	switch (dir) {
		case 1: // Forward
			speed_t = speed * 1;
			break;
		
		case 2: // Backward
			speed_t = speed * -1;
			break;
		
		default: // Stop
			speed_t = 0;

	}
	
	/*
	send(0x20 | (1 << (ch - 1)), (uint8_t)speed_t);
	
	return sync_data();
	*/
	
	sendQ(0x20 | (1 << (ch - 1)), (uint8_t)speed_t);
	return true;
}

bool iKB_1::servo(uint8_t ch, uint8_t angle) {
	if (ch < 1 || ch > 6) {
		return false;
	}
	
	/*
	send(0x40 | (1 << (ch - 1)), (uint8_t)angle);
	
	return sync_data();
	*/
	
	sendQ(0x40 | (1 << (ch - 1)), (uint8_t)angle);
	return true;
}

bool iKB_1::servo2(uint8_t ch, uint8_t dir, uint8_t speed) {
	if (ch < 1 || ch > 6) {
		return false;
	}
	
	speed = fmax(speed, 0);
	speed = fmin(speed, 100);
	
	uint8_t angle; 
	if (dir == 1) {
		angle = 90 - (speed * 90 / 100); // Forward
	} else if (dir == 2) {
		angle = 90 + (speed * 90 / 100); // Backward
	} else {
		return false;
	}

	return servo(ch, angle);
}

bool iKB_1::uart_config(unsigned long baud) {
	uartBaud = baud;
	return true;
}

bool iKB_1::uart_write(char data) {
	char dataStr[] = { data, 0 };
	return uart_write(dataStr);
}

bool iKB_1::uart_write(bool data) {
	return uart_write((char)('0' + (data ? 1 : 0)));
}

bool iKB_1::uart_write(double data) {
	char dataStrBuffer[20];
	memset(dataStrBuffer, 0, sizeof dataStrBuffer);
	sprintf(dataStrBuffer,"%f", data);
	return uart_write(dataStrBuffer);
}

bool iKB_1::uart_write(const char* data) {
	if (!sync_data()) {
		return false;
	}
	
	uint8_t baudToBit;
	if (uartBaud == 2400) {
		baudToBit = 0b00;
	} else if (uartBaud == 9600) {
		baudToBit = 0b01;
	} else if (uartBaud == 57600) {
		baudToBit = 0b10;
	} else if (uartBaud == 115200) {
		baudToBit = 0b11;
	} else {
		return false;
	}
	
	int len = strlen(data);
	len = fmin(len, 64); // Limit 64 bytes
	
	dataBuffer.write.data.command = 0x04 | baudToBit;
	memcpy(&dataBuffer.write.data.block[1], data, len);
	dataBuffer.write.length = len + 1; // User data length + 1 byte command
	dataBuffer.read.length = 0;
	
	dataBuffer.old = false;
	
	return sync_data();
}

bool iKB_1::uart_write_line(char data) {
	char dataStr[] = { data, 0 };
	return uart_write_line(dataStr);
}

bool iKB_1::uart_write_line(bool data) {
	return uart_write_line((char)('0' + (data ? 1 : 0)));
}

bool iKB_1::uart_write_line(double data) {
	char dataStrBuffer[20];
	memset(dataStrBuffer, 0, sizeof dataStrBuffer);
	sprintf(dataStrBuffer,"%f\n", data);
	return uart_write(dataStrBuffer);
}

bool iKB_1::uart_write_line(const char* data) {
	int data_length = strlen(data);
	char strBuffer[data_length + 2]; // 1 byte for new line (\n) and 1 byte for end of string
	memcpy(strBuffer, data, data_length);
	strBuffer[data_length] = '\n'; // new line
	strBuffer[data_length + 1] = 0; // end of string
	
	return uart_write(strBuffer);
}

uint16_t iKB_1::uart_available() {
	uint8_t newDataIniKB_1 = 0;
	uint8_t readCount = 0;
	
	if (!send(0x01, (int)1)) {
		#ifdef IKB_1_DEBUG
		char bufferHere[40];
		sprintf(bufferHere, "Read serial available fail");
		uart_write_bytes(UART_NUM_0, bufferHere, strlen(bufferHere));
		#endif
	}
		
	if (sync_data()) {
		newDataIniKB_1 = dataBuffer.read.data.block[0];
			
		#ifdef IKB_1_DEBUG
		char bufferHere[20];
		sprintf(bufferHere, "Data new (iKB-1): %d\n", newDataIniKB_1);
		uart_write_bytes(UART_NUM_0, bufferHere, strlen(bufferHere));
		#endif
			
		while(newDataIniKB_1 > 0) {
			readCount = uart_read_from_iKB_1(newDataIniKB_1);
			
			#ifdef IKB_1_DEBUG
			char bufferHere[20];
			sprintf(bufferHere, "Read: %d\n", readCount);
			uart_write_bytes(UART_NUM_0, bufferHere, strlen(bufferHere));
			#endif
			
			if (readCount > 0) {
				for (int inx=0;inx<readCount;inx++) {
					iKB_1_Data_Enqueue(&iKB_1_qSerailRead, dataBuffer.read.data.block[inx]);
				}
			}
			newDataIniKB_1 = newDataIniKB_1 - readCount;
		}
	} else { // some error !
		#ifdef IKB_1_DEBUG
		char bufferHere[20];
		sprintf(bufferHere, "Some Error !\n");
		uart_write_bytes(UART_NUM_0, bufferHere, strlen(bufferHere));
		#endif
			
		newDataIniKB_1 = 0;
	}
	
	return iKB_1_qSerailRead.count;
}

char iKB_1::uart_read() {
	// return uart_read(1)[0];
	return iKB_1_Data_Dequeue(&iKB_1_qSerailRead);
}

char* iKB_1::uart_read(uint8_t count) {
	count = fmin(count, 256);
	count = fmin(iKB_1_qSerailRead.count, count);
	
	memset(strBuffer, 0, sizeof strBuffer);
	for (int inx=0;inx<count;inx++) {
		strBuffer[inx] = uart_read();
		
		#ifdef IKB_1_DEBUG
		/*
		char bufferHere[10];
		sprintf(bufferHere, "C: %c\n", strBuffer[inx]);
		uart_write_bytes(UART_NUM_0, bufferHere, strlen(bufferHere));
		*/
		#endif
	}
	
	#ifdef IKB_1_DEBUG
	char bufferHere[80];
	sprintf(bufferHere, "Data Read (%d): %s\n", count, strBuffer);
	uart_write_bytes(UART_NUM_0, bufferHere, strlen(bufferHere));
	#endif
	
	return strBuffer;
}

int iKB_1::uart_read_from_iKB_1(uint8_t count) {
	// count = fmin(count, 63); // 63 bytes for character and 1 byte for end of string (\0)
	count = fmin(count, 30); // limit 30 bytes per round
	
	memset(dataBuffer.read.data.block, 0, sizeof dataBuffer.read.data.block);
	if (!send(0x02, count, count)) {
		return 0;
	}
	
	if (sync_data(count * 300)) {
		#ifdef IKB_1_DEBUG
		char bufferHere[80];
		sprintf(bufferHere, "Data Read From iKB-1: %s\n", dataBuffer.read.data.block);
		uart_write_bytes(UART_NUM_0, bufferHere, strlen(bufferHere));
		#endif
		
		return count;
	}
	
	return 0;
}

char* iKB_1::uart_read_string(uint32_t timeout) {
	uint32_t wait_max_time = timeout;
	uint32_t lastUpdate = esp_timer_get_time();
	uint32_t nowTime;
	
	bool overflowBuffer = false;
	uint16_t inxStr = 0;
	memset(strBuffer, 0, sizeof strBuffer);
	
	while(1) {
		nowTime = esp_timer_get_time();
		if ((nowTime - lastUpdate) > (timeout * 1000)) {
			break;
		}
		
		if (overflowBuffer) {
			break;
		}
		
		uint16_t dataCount = uart_available();
		while (dataCount--) {
			if (inxStr > ((sizeof strBuffer) - 1)) {
				overflowBuffer = true;
				break;
			}
			strBuffer[inxStr++] = iKB_1_Data_Dequeue(&iKB_1_qSerailRead);
			lastUpdate = esp_timer_get_time();
		}
	}
	
	return strBuffer;
}

char* iKB_1::uart_read_line(uint32_t timeout) {
	uart_read_until("\n", timeout);
	
	return strBuffer;
}

char* iKB_1::uart_read_until(char* until, uint32_t timeout) {
	uint32_t wait_max_time = timeout;
	uint32_t lastUpdate = esp_timer_get_time();
	uint32_t nowTime;
	
	bool foundChar = false;
	bool overflowBuffer = false;
	uint16_t inxStr = 0;
	memset(strBuffer, 0, sizeof strBuffer);
	
	while(1) {
		nowTime = esp_timer_get_time();
		if ((nowTime - lastUpdate) > (timeout * 1000)) {
			break;
		}
		
		if (overflowBuffer || foundChar) {
			break;
		}
		
		uint16_t dataCount = uart_available();
		while (dataCount--) {
			if (inxStr > ((sizeof strBuffer) - 1)) {
				overflowBuffer = true;
				break;
			}
			char c = iKB_1_Data_Dequeue(&iKB_1_qSerailRead);
			if (c == until[0]) {
				foundChar = true;
				break;
			}
			strBuffer[inxStr++] = c;
			lastUpdate = esp_timer_get_time();
		}
	}
	
	return strBuffer;
}

// Circle Queue
void iKB_1_Enqueue(iKB_1_Queue *q, iKB_1_CommandData data) {
	if (q->count == iKB_1_BUFFER_SIZE) return;

	q->rear = q->rear == iKB_1_BUFFER_SIZE ? 0 : q->rear + 1;
	q->data[q->rear] = data;
	q->count++;
	
	if (q->front == -1) q->front = 0;
}

iKB_1_CommandData iKB_1_Dequeue(iKB_1_Queue *q) {
	iKB_1_CommandData data;
	
	if (q->count == 0 || q->front == -1) return data;

	data = q->data[q->front];
	q->front++;
	if (q->front == iKB_1_BUFFER_SIZE) q->front = 0;
	q->count--;
	
	if (q->count == 0) {
		q->front = -1;
		q->rear  = -1;
	}
	
	return data;
}

// Circle Queue (2)
void iKB_1_Data_Enqueue(iKB_1_DataQueue *q, uint8_t data) {
	if (q->count == iKB_1_DATA_BUFFER_SIZE) { // if queue is full
		if (iKB_1_DATA_QUEUE_ROLL) {
			iKB_1_Data_Dequeue(q);
		}
		return;
	}
	
	q->rear = q->rear == iKB_1_DATA_BUFFER_SIZE ? 0 : q->rear + 1;
	q->data[q->rear] = data;
	q->count++;
	
	if (q->front == -1) q->front = 0;
}

uint8_t iKB_1_Data_Dequeue(iKB_1_DataQueue *q) {
	if (q->count == 0 || q->front == -1) return 0;

	uint8_t data = q->data[q->front];
	q->front++;
	if (q->front == iKB_1_DATA_BUFFER_SIZE) q->front = 0;
	q->count--;
	
	if (q->count == 0) {
		q->front = -1;
		q->rear  = -1;
	}
	
	return data;
}

#endif
