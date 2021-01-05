#ifndef __AD5142__
#define __AD5142__
#include <stdint.h>
#include <SPI.h>

typedef union cmd{
    uint16_t u;
    struct {
        unsigned int data : 8;
        unsigned int address : 4;
        unsigned int control : 4;
    }struc;
}cmd;

// COMMANDS OP TRUTH TABLE (see datasheet page 22/32 https://www.analog.com/en/products/ad5142.html )
#define OP_NOP 0
#define OP_WRITE_SERIALREG_TO_RADC 1
#define OP_WRITE_SERIALREG_TO_INPUTREG 2
#define OP_READ_BACK_REGISTER 3
#define OP_RDAC_AND_EEPROM_COPY 7
#define OP_SWRESET 11
#define OP_SWSHUTDOWN 12
#define RDAC1 0
#define RDAC2 1
#define READBACK_EEPROM_SELECT 1
#define READBACK_RDAC_SELECT   3
#define STORED_RDAC1_CHANNEL 0
#define STORED_RDAC2_CHANNEL 2

class AD5142
{
private:
    /* data */
    SPIClass *spi_port; //SPI TO USE EG: SPI, SPI1, SPI2 ...
    unsigned int wiper1, wiper2;
    unsigned int LE_PIN; //SPI LATCH ENABLE PIN 

    unsigned int spi_write(unsigned int data);
    void write_to_rdac(unsigned char val, unsigned char rdac_n);
    void write_to_input_register(unsigned char val, unsigned char rdac_n);
    unsigned char readback_device(unsigned char contents, unsigned char rdac_n);

public:
    AD5142(SPIClass *port, unsigned int LE_PIN)
    {
        this->spi_port = port;
        this->LE_PIN = LE_PIN;
        this->wiper1 = 5000;
        this->wiper2 = 5000;
    }

    //to be made private
    void copyRDACtoEEPROM(unsigned char rdac_n);
    void copyEEPROMtoRDAC(unsigned char rdac_n);
    void software_reset();

    


    //final public functions
    void setResistance(unsigned char wiper, int resistance);
    unsigned int getWiper1(); //TODO: convert to single function
    unsigned int getWiper2(); //TODO: Convert to sngle function
   
    //TODO
    //int saveSettingsToChip(){}
    //int loadChipSettings(){}
    //

};





#endif