

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "main.h"

extern SPI_HandleTypeDef hspi1;

/**
 * @brief SPI1 GPIO Configuration
 */
void spi_GPIO_config(void);

/**
 * @brief SPI1 Configuration
 */
bool spi_config(void);

/**
 * @brief SPI CS1 RFID enable/disable
 */
void spi_CS1_enable(void);
void spi_CS1_disable(void);


#endif /* INC_SPI_H_ */
