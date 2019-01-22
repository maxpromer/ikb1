#ifndef __iKB_1_H__
#define __iKB_1_H__

#include <math.h>
#include <string.h>

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "driver/uart.h"
#include "kidbright32.h"

// #define IKB_1_DEBUG
#define IKB_1_I2C_CLOCK 100E3

extern I2CDev I2C1;

class iKB_1 : public Device {
	private:		
		enum {
			s_detect,
			s_runing,
			s_wait,
			s_error
		} state;
		TickType_t tickcnt, polling_tickcnt;

		uint8_t read_data[64]; // Max 64 byte for read buffer
		
		uint8_t errCount = 0;
		
		unsigned long uartBaud = 9600;
		
		char strBuffer[257];
		
		// method
		void i2c_setClock(uint32_t clock) ;
		bool send(uint8_t command) ;
		bool send(uint8_t command, uint8_t parameter) ;
		bool send(uint8_t command, uint8_t parameter, int request_length) ;
		bool send(uint8_t command, int request_length) ;
		int uart_read_from_iKB_1(uint8_t count) ;

	public:
		// constructor
		iKB_1(int bus_ch, int dev_addr) ;
		
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		bool reset() ;
		uint8_t digital_read(uint8_t ch, bool pullup = false) ;
		bool digital_write(uint8_t ch, uint8_t value) ;
		int analog_read(uint8_t ch) ;
		bool motor(uint8_t ch, uint8_t dir, uint8_t speed) ;
		bool servo(uint8_t ch, uint8_t angle) ;
		bool servo2(uint8_t ch, uint8_t dir, uint8_t speed) ;
		
		bool uart_config(unsigned long baud) ;
		bool uart_write(char data) ;
		bool uart_write(bool data) ;
		bool uart_write(double data) ;
		bool uart_write(const char* data) ;
		bool uart_write_line(char data) ;
		bool uart_write_line(bool data) ;
		bool uart_write_line(double data) ;
		bool uart_write_line(const char* data) ;
		
		uint16_t uart_available() ;
		char uart_read() ;
		char* uart_read(uint8_t count) ;
		char* uart_read_string(uint32_t timeout = 1000) ;
		char* uart_read_line(uint32_t timeout = 1000) ;
		char* uart_read_until(char* until, uint32_t timeout = 1000) ;
		
};

// Circle Queue 2
#define iKB_1_DATA_BUFFER_SIZE 256
#define iKB_1_DATA_QUEUE_ROLL 1

typedef struct {
	int count;
	int rear;
	int front;
	uint8_t data[iKB_1_DATA_BUFFER_SIZE];
} iKB_1_DataQueue;

static iKB_1_DataQueue iKB_1_qSerailRead;

void iKB_1_Data_Enqueue(iKB_1_DataQueue *q, uint8_t data) ;
uint8_t iKB_1_Data_Dequeue(iKB_1_DataQueue *q) ;

#endif
