
int baudrate;

void Delay (uint16_t nCount);
void Default_data_write_to _eeprom(void);
void Read_data_from_eeprom (void);
void gpio_init(void);
void spi_init(void);

int main (void)
{
  gpio_init();
  Default_data_write_to _eeprom();
  Read_data_from_eeprom();
  uart_init(baudrate);
  spi_init();
  setup();              // configure the cc2500 in required format.

  while (1)
  {
      if(data_received_RF)
      {
              data_received_RF = 0;
              send_data_uart(uart_send_buff);
              
      }
      else if(data_received_UART)
      {
              data_received_UART = 0
              send_data_rf(RF_send_buff);
      }
  }
}

/**
  * @brief  Delay.
  * @param  nCount
  * @retval None
  */
void Delay(uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}