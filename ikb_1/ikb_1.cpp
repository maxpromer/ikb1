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
				reset();
				
				// Go to main state
				state = s_runing;
			} else {
				state = s_error;
			}
			break;
		
		case s_runing: {

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

// Send only, no parameter, no request
bool iKB_1::send(uint8_t command) {
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, command, true);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	return ret == ESP_OK;
}

// Send command and parameter, no request
bool iKB_1::send(uint8_t command, uint8_t parameter) {
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, command, true);
	i2c_master_write_byte(cmd, parameter, true);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	return ret == ESP_OK;
}

// Send command and parameter and request
bool iKB_1::send(uint8_t command, uint8_t parameter, int request_length) {
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, command, true);
	i2c_master_write_byte(cmd, parameter, true);
	if (request_length > 1) {
        i2c_master_read(cmd, read_data, request_length - 1, I2C_MASTER_ACK);
    }
	i2c_master_read_byte(cmd, read_data + request_length - 1, I2C_MASTER_LAST_NACK);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	return ret == ESP_OK;
}

// Send command and request, no parameter 
bool iKB_1::send(uint8_t command, int request_length) {
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, command, true);
	if (request_length > 1) {
        i2c_master_read(cmd, read_data, request_length - 1, I2C_MASTER_ACK);
    }
	i2c_master_read_byte(cmd, read_data + request_length - 1, I2C_MASTER_LAST_NACK);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	return ret == ESP_OK;
}

bool iKB_1::reset() {
	return send((uint8_t)0x0);
}

uint8_t iKB_1::digital_read(uint8_t ch, bool pullup) {
	// if (ch < 0 || ch > 7) { // warning: comparison is always false due to limited range of data type
	if (ch > 7) {
		return 0;
	}
	
	if (!send(0x08 + ch, (pullup ? 3 : 2), 1)) {
		return 0;
	}
	
	return read_data[0] != 0;
}

bool iKB_1::digital_write(uint8_t ch, uint8_t value) {
	if (ch > 7) {
		return false;
	}

	return send(0x08 + ch, (uint8_t)(value != 0 ? 1 : 0));
}

int iKB_1::analog_read(uint8_t ch) {
	if (ch > 7) {
		return 0;
	}
	
	if (!send(0x80 + (ch << 4), (int)2)) {
		return false;
	}
	
	return (read_data[0]<<8)|read_data[1];
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

	return send(0x20 | (1 << (ch - 1)), (uint8_t)speed_t);
}

bool iKB_1::servo(uint8_t ch, uint8_t angle) {
	if (ch < 1 || ch > 6) {
		return false;
	}

	return send(0x40 | (1 << (ch - 1)), (uint8_t)angle);
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

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, 0x04 | baudToBit, true);
	i2c_master_write(cmd, (uint8_t*)data, len, true);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	
	return ret == ESP_OK;
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

	newDataIniKB_1 = read_data[0];
			
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
				iKB_1_Data_Enqueue(&iKB_1_qSerailRead, read_data[inx]);
			}
		}
		newDataIniKB_1 = newDataIniKB_1 - readCount;
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
	
	memset(read_data, 0, sizeof read_data);
	if (!send(0x02, count, count)) {
		return 0;
	}
	
	#ifdef IKB_1_DEBUG
	char bufferHere[80];
	sprintf(bufferHere, "Data Read From iKB-1: %s\n", dataBuffer.read.data.block);
	uart_write_bytes(UART_NUM_0, bufferHere, strlen(bufferHere));
	#endif
		
	return count;
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
