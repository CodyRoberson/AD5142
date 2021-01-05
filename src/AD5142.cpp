#include "AD5142.h"

unsigned int AD5142::spi_write(unsigned int data)
{
    unsigned int reta = 0;
    this->spi_port->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
    digitalWrite(this->LE_PIN, LOW);
   
    delayMicroseconds(1);

    reta = this->spi_port->transfer((data >> 8) & 0xFF);
    reta = reta << 8;
    reta = reta | this->spi_port->transfer(data & 0xFF);

    digitalWrite(this->LE_PIN, HIGH);

    this->spi_port->endTransaction();
    return reta;
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

void AD5142::setResistance(unsigned char wiper, int resistance){
    unsigned int c = 0, readback = 0;
    double x = round(-0.0256 * (resistance - 10000));
    int d = (int) x;

    if (d >= 256){
        d = 255;
    }
    if (d < 1)
    {
        d = 1;
    }
    if(wiper == 1){
        this->write_to_rdac((unsigned char) d, RDAC1);
        c = readback_device(READBACK_RDAC_SELECT, RDAC1);
        readback = (unsigned int) (((256.0 - (double) c)/256.0) * 10000.0);
        this->wiper1 = readback;
    }
    else if(wiper == 2)
    {
        this->write_to_rdac((unsigned char) d, RDAC2);
        c = readback_device(READBACK_RDAC_SELECT, RDAC2);
        readback = int (((256.0 - (double) c)/256.0) * 10000.0);
        this->wiper2 = readback;
    }
    else {
        return;
    }

    
    
}

unsigned int AD5142::getWiper1()
{
    return this->wiper1;
}
unsigned int AD5142::getWiper2()
{
    return this->wiper2;
}
/**
 * @brief     
 * 
 *  u
    return d;

    unsigned char c;
    unsigned int d;

    return d;
 * 
 */