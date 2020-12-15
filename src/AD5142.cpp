#include "AD5142.h"

unsigned int AD5142::spi_write(unsigned int data)
{
    unsigned int ret = 0;
    this->spi_port->beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    digitalWrite(this->LE_PIN, LOW);
    ret = this->spi_port->transfer16(data & 0xFFFF);
    digitalWrite(this->LE_PIN, HIGH);
    this->spi_port->endTransaction();
    return ret;
}

void AD5142::write_to_rdac(unsigned char val, unsigned char rdac_n)
{
    cmd c;
    if (rdac_n > 1)
        rdac_n = 1;

    c.struc.control = OP_WRITE_SERIALREG_TO_RADC;
    c.struc.address = rdac_n;
    c.struc.data = val;

    spi_write(c.u);
}

void AD5142::write_to_input_register(unsigned char val, unsigned char rdac_n)
{
    cmd c;
    if (rdac_n > 1)
        rdac_n = 1;

    c.struc.control = OP_WRITE_SERIALREG_TO_INPUTREG;
    c.struc.address = rdac_n;
    c.struc.data = val;

    spi_write(c.u);
}

unsigned char AD5142::readback_device(unsigned char contents, unsigned char rdac_n)
{
    cmd c, d;
    if (rdac_n > 1)
        rdac_n = 1;
    c.struc.control = OP_READ_BACK_REGISTER;
    
    if (rdac_n == RDAC1)
        c.struc.address = STORED_RDAC1_CHANNEL;
    else
        c.struc.address = STORED_RDAC2_CHANNEL;
    
    c.struc.data = contents;

    d.u = spi_write(c.u);
    return d.struc.data;

}

void AD5142::copyRDACtoEEPROM(unsigned char rdac_n)
{
    cmd c;
    c.struc.control = OP_RDAC_AND_EEPROM_COPY;
    c.struc.address = rdac_n;
    c.struc.data = 1;
    spi_write(c.u);
}

void AD5142::copyEEPROMtoRDAC(unsigned char rdac_n)
{
    cmd c;
    c.struc.control = OP_RDAC_AND_EEPROM_COPY;
    c.struc.address = rdac_n;
    c.struc.data = 0;
    spi_write(c.u);
}

void AD5142::software_reset(){
    cmd c;
    c.struc.control = OP_SWRESET;
    spi_write(c.u);
}

void AD5142::setResistance(unsigned char wiper, unsigned int resistance){
    if(wiper == 1)
        ; //TODO: Implement 
    else if(wiper == 2)
        ; //TODO: Implement
    else
        ; //TODO: I just don't know anymore
    
    
}


unsigned int AD5142::getWiper1()
{
    unsigned int c;
    c = readback_device(READBACK_RDAC_SELECT, RDAC1);
}
unsigned int AD5142::getWiper2()
{
    unsigned int c;
    c = readback_device(READBACK_RDAC_SELECT, RDAC2);
}
