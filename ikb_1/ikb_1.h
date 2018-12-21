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

/*
enum {
	iKB_CHANEL1 = 1,
	iKB_CHANEL2 = 2,
	iKB_CHANEL3 = 3,
	iKB_CHANEL4 = 4,
	iKB_CHANEL5 = 5,
	iKB_CHANEL6 = 6,
	iKB_CHANEL7 = 7,
	iKB_CHANEL8 = 8
};
*/

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
		
		struct {
			struct {
				union {
					uint8_t block[65]; // 1 byte command + 64 bytes parameters
					struct {
						uint8_t command;
						uint8_t parameter;
					};
				} data;
				int length; // Data length for write
			} write;
			
			struct {
				union {
					uint8_t block[64]; // Max 64 byte for read buffer
					/*
					struct {
					} byte;
					*/
				} data;
				int length; // Data length for request
			} read;
			
			bool old;
		} dataBuffer;
		
		uint8_t errCount = 0;
		
		unsigned long uartBaud = 9600;
		
		// method
		void i2c_setClock(uint32_t clock) ;
		bool sync_data(uint16_t wait_time = 1000) ;
		bool send(uint8_t command) ;
		bool send(uint8_t command, uint8_t parameter) ;
		bool sendQ(uint8_t command, uint8_t parameter) ;
		bool send(uint8_t command, uint8_t parameter, int request_length) ;
		bool send(uint8_t command, int request_length) ;

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
		bool reset(bool sync) ;
		uint8_t digital_read(uint8_t ch, bool pullup = false) ;
		bool digital_write(uint8_t ch, uint8_t value) ;
		int analog_read(uint8_t ch) ;
		bool motor(uint8_t ch, uint8_t dir, uint8_t speed) ;
		bool servo(uint8_t ch, uint8_t angle) ;
		bool servo2(uint8_t ch, uint8_t dir, uint8_t speed) ;
		
		bool uart_config(unsigned long baud) ;
		uint8_t uart_available() ;
		bool uart_write(char data) ;
		bool uart_write(bool data) ;
		bool uart_write(double data) ;
		bool uart_write(const char* data) ;
		bool uart_write_line(char data) ;
		bool uart_write_line(bool data) ;
		bool uart_write_line(double data) ;
		bool uart_write_line(const char* data) ;
		
		char uart_read() ;
		char* uart_read(uint8_t count) ;
		char* uart_read_string();
		char* uart_read_line();
		char* uart_read_until(char until);
		
};

// 
typedef struct {
	uint8_t command;
	uint8_t parameter;
} iKB_1_CommandData;

// Circle Queue
#define iKB_1_BUFFER_SIZE 20

typedef struct {
	int count;
	int rear;
	int front;
	iKB_1_CommandData data[iKB_1_BUFFER_SIZE];
} iKB_1_Queue;

static iKB_1_Queue iKB_1_qWrite;

void iKB_1_Enqueue(iKB_1_Queue *q, iKB_1_CommandData data) ;
iKB_1_CommandData iKB_1_Dequeue(iKB_1_Queue *q) ;

#endif
