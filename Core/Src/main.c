#include "main.h"
#define UID_byte 4
#define MAX_SPAM 3
#define SECOND_WAIT 60
#define MAX_UIDS 3                      // Maximum UID quantity you want to save
#define MASTER_STATUS_ADDRESS 0x08007C00 // page 31
#define UID_MASTER_ADDRESS 0x8008000     // page 32
#define UID_NUM_ADDRESS 0x8008400        // page 33
#define UID_START_ADDRESS 0x8008800      // page 34

uint8_t uid[UID_byte];
uint8_t previousMillis = 0;
uint8_t currentMillis = 0;

uint8_t resultArray1[UID_byte];
uint8_t uidMasterArray[UID_byte];

char count_spam = 0;
char dem = 0;
char num_uids = 0; // Stored UID count.

bool DownInterrupt = false;
bool EnterInterupt = false;
bool master_setup;
bool menu1_status = false;
bool menu2_status = false;
// Prototype
void initializeHardware();
void Master_Setup_Display();
void handleSecurityCard();
void Main_Display();
void Menu1();
void Menu2();
void Del_All_Card();
void Del_1_Card();
void Add_New_Card();
void UID_Master_Setup();
void STATUS_OK();
void STATUS_NOT_OK();
void WAIT_TO_SCAN_AGAIN();
void ConvertFlashValue(uint32_t flashAddress, uint8_t *resultArray);
//----------------------------------------------------

int main()
{
    // Initialization
    initializeHardware();
    // UID Master Setup
    while (Flash_Read_2Byte(MASTER_STATUS_ADDRESS))
    {
        UID_Master_Setup();
    }
    handleSecurityCard();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
    case ENTER:
        EnterInterupt = true;
        EXTI->IMR &= ~(1UL << 12);
        break;
    case DOWN:
        DownInterrupt = true;
        if (menu2_status)
            menu2_status = false;
        EXTI->IMR &= ~(1UL << 13);
    }
}

void UID_Master_Setup(void)
{
    Flash_Erase(MASTER_STATUS_ADDRESS); // Free up page storing MASTER_STATUS
    Flash_Erase(UID_MASTER_ADDRESS);    // Free up page storing MASTER_STATUS
    Flash_Erase(UID_NUM_ADDRESS);       // Free up page storing num_uids
    Master_Setup_Display();
    if (rc522_checkCard(uid))
    {
        STATUS_OK();
        master_setup = false;
        Flash_Write_2Byte(MASTER_STATUS_ADDRESS, master_setup);                                   // Store status master
        Flash_Write_2Byte(UID_NUM_ADDRESS, num_uids);                                             // Store num_uids
        Flash_Write_Array(UID_MASTER_ADDRESS, (uint8_t *)uid, (UID_byte - 2) * sizeof(uint16_t)); // Store master uid
        HAL_Delay(500);
    }
}
void Main_Display(void)
{
    dem = 0;
    Clear();
    SetCursor(0, 0);
    WriteString("***SCAN YOUR***");
    SetCursor(6, 1);
    WriteString("CARD");
    menu1_status = false;
    menu2_status = false;
    count_spam = 0;
    HAL_GPIO_TogglePin(GPIOA, LOCK);
}
void Menu1(void)
{
    switch (dem)
    {
    case 1:
        Clear();
        SetCursor(0, 0);
        WriteString(">BACK");
        SetCursor(0, 1);
        WriteString(" ADD NEW CARD");
        break;
    case 2:
        Clear();
        SetCursor(0, 0);
        WriteString(" BACK");
        SetCursor(0, 1);
        WriteString(">ADD NEW CARD");
        break;
    case 3:
        Clear();
        SetCursor(0, 0);
        WriteString(">DELETE 1 CARD");
        SetCursor(0, 1);
        WriteString(" DELETE ALL CARD");
        break;
    case 4:
        Clear();
        SetCursor(0, 0);
        WriteString(" DELETE 1 CARD");
        SetCursor(0, 1);
        WriteString(">DELETE ALL CARD");
        break;
    }
}
void Menu2(void)
{
    switch (dem)
    {
    case 1:
        Main_Display();
        break;
    case 2:
        Add_New_Card();
        break;
    case 3:
        Del_1_Card();
        break;
    case 4:
        Del_All_Card();
        break;
    }
}
void Add_New_Card(void)
{
    ConvertFlashValue(UID_MASTER_ADDRESS, uidMasterArray);
    EXTI->IMR |= (1UL << 12);
BACK1:
    Clear();
    HAL_Delay(10);
    SetCursor(1, 0);
    WriteString("ADD YOUR NEW");
    SetCursor(1, 1);
    WriteString("SECURITY CARD");
    while (menu2_status)
    { // CHECK CARD IS EXIST OR NOT
        bool duplicate = false;
        if (rc522_checkCard(uid))
        {
            if (memcmp(uidMasterArray, uid, UID_byte) == 0) // Compare with uid master
                goto HERE1;
            for (int i = 0; i < num_uids; ++i)
            {
                ConvertFlashValue(UID_START_ADDRESS + 0x400 * i, resultArray1);
                if ((memcmp(resultArray1, uid, UID_byte) == 0))
                {
                    duplicate = true;
                HERE1:
                    STATUS_NOT_OK();
                    Clear();
                    SetCursor(2, 0);
                    WriteString("CARD ALREADY");
                    SetCursor(2, 1);
                    WriteString("EXISTS !!!");
                    HAL_Delay(1000);
                    break;
                }
            }
            if (!duplicate && num_uids < MAX_UIDS && (memcmp(uidMasterArray, uid, UID_byte) != 0))
            {
                // Save uid to array
                STATUS_OK();
                Clear();
                SetCursor(1, 0);
                WriteString("CARD IS ADDED");
                SetCursor(2, 1);
                WriteString("SUCCESFULLY");
                HAL_Delay(1000);
                Flash_Write_Array(UID_START_ADDRESS + 0x400 * num_uids, (uint8_t *)uid, (UID_byte - 2) * sizeof(uint16_t));
                ++num_uids;
                Flash_Erase(UID_NUM_ADDRESS);
                Flash_Write_2Byte(UID_NUM_ADDRESS, num_uids);
            }
            else if (!duplicate && num_uids == MAX_UIDS)
            {
                STATUS_NOT_OK();
                Clear();
                SetCursor(0, 0);
                WriteString("THE SECURITY");
                SetCursor(0, 1);
                WriteString("CARD LIST IS FULL");
                HAL_Delay(1000);
            }
            goto BACK1;
        }
    }
    menu2_status = true;
    EnterInterupt = false;
}
void Del_1_Card(void)
{
    ConvertFlashValue(UID_MASTER_ADDRESS, uidMasterArray);
    EXTI->IMR |= (1UL << 12);
    int index_delete;
BACK2:
    Clear();
    HAL_Delay(10);
    SetCursor(1, 0);
    WriteString("SCAN YOUR CARD");
    bool card_exist = false;
    while (menu2_status)
    {
        if (rc522_checkCard(uid))
        {
            if ((memcmp(uidMasterArray, uid, UID_byte) == 0))
            {
                STATUS_NOT_OK();
                Clear();
                SetCursor(0, 0);
                WriteString("MASTER CARD CAN");
                SetCursor(0, 1);
                WriteString("NOT BE DELETED");
                HAL_Delay(1000);
            }
            else
            {
                for (int i = 0; i < num_uids; ++i)
                {
                    ConvertFlashValue(UID_START_ADDRESS + 0x400 * i, resultArray1);
                    if (memcmp(resultArray1, uid, UID_byte) == 0)
                    {
                        index_delete = i;
                        card_exist = true;
                        break;
                    }
                }
                if (card_exist)
                {
                    for (int i = index_delete; i < num_uids - 1; ++i)
                    {
                        ConvertFlashValue(UID_START_ADDRESS + 0x400 * (i + 1), resultArray1);
                        Flash_Erase(UID_START_ADDRESS + 0x400 * (i + 1));
                        Flash_Erase(UID_START_ADDRESS + 0x400 * i);
                        Flash_Write_Array(UID_START_ADDRESS + 0x400 * i, (uint8_t *)resultArray1, (UID_byte - 2) * sizeof(uint16_t));
                    }
                    STATUS_OK();
                    Clear();
                    SetCursor(2, 0);
                    WriteString("YOUR CARD IS");
                    SetCursor(2, 1);
                    WriteString("DELETED");
                    HAL_Delay(1000);
                    --num_uids;
                    Flash_Erase(UID_NUM_ADDRESS);
                    Flash_Write_2Byte(UID_NUM_ADDRESS, num_uids); // Update num_uids for flash
                }
                else
                {
                    STATUS_NOT_OK();
                    Clear();
                    SetCursor(1, 0);
                    WriteString("SECURITY CARD");
                    SetCursor(1, 1);
                    WriteString("IS NOT EXIST");
                    HAL_Delay(1000);
                }
            }
            goto BACK2;
        }
    }
    menu2_status = true;
    EnterInterupt = false;
}
void Del_All_Card(void)
{
    if (num_uids == 0)
    {
        STATUS_NOT_OK();
        Clear();
        SetCursor(1, 0);
        WriteString("THERE IS NO");
        SetCursor(1, 1);
        WriteString("SECURITY CARDS");
        HAL_Delay(1000);
    }
    else
    {
        for (int i = 0; i < num_uids; ++i)
            Flash_Erase(UID_START_ADDRESS + 0x400 * i);
        num_uids = 0;
        Flash_Write_2Byte(UID_NUM_ADDRESS, num_uids);
        STATUS_OK();
        Clear();
        SetCursor(1, 0);
        WriteString("SECURITY CARDS");
        SetCursor(1, 1);
        WriteString("ARE DELETED");
        HAL_Delay(1000);
    }
}
void STATUS_OK(void)
{
    HAL_GPIO_TogglePin(GPIOA, GREENLED);
    HAL_GPIO_TogglePin(GPIOA, BUZZER);
    HAL_Delay(400);
    HAL_GPIO_TogglePin(GPIOA, GREENLED);
    HAL_GPIO_TogglePin(GPIOA, BUZZER);
}
void STATUS_NOT_OK(void)
{
    HAL_GPIO_TogglePin(GPIOA, REDLED);
    HAL_GPIO_TogglePin(GPIOA, BUZZER);
    HAL_Delay(400);
    HAL_GPIO_TogglePin(GPIOA, REDLED);
    HAL_GPIO_TogglePin(GPIOA, BUZZER);
}
void initializeHardware()
{
    HAL_Init();
    rcc_systemClockConfig();
    LCD_config_gpio();
    LCD_Init();
    spi_GPIO_config();
    spi_config();
    rc522_init();
    exti_buttonConfig();
    gpio_Init();
}
void handleSecurityCard()
{
    num_uids = Flash_Read_2Byte(UID_NUM_ADDRESS);
    ConvertFlashValue(UID_MASTER_ADDRESS, uidMasterArray);
    Clear();
    while (1)
    {
        if (dem == 0)
        {
            SetCursor(0, 0);
            WriteString("***SCAN YOUR***");
            SetCursor(6, 1);
            WriteString("CARD");
        }
        if (rc522_checkCard(uid) && !(menu1_status))
        {
            if (memcmp(uidMasterArray, uid, UID_byte) == 0)
            {
                STATUS_OK();
                HAL_GPIO_TogglePin(GPIOA, LOCK);
                ++dem;
                menu1_status = true;
                Menu1();
            }
            else
            {
                bool valid_card = false;
                for (int i = 0; i < num_uids; i++)
                {
                    ConvertFlashValue(UID_START_ADDRESS + 0x400 * i, resultArray1);
                    if ((memcmp(resultArray1, uid, UID_byte) == 0) || (memcmp(uidMasterArray, uid, UID_byte) == 0))
                    {
                        STATUS_OK();
                        valid_card = true;
                        Clear();
                        SetCursor(0, 0);
                        WriteString("*SECURITY CARD*");
                        SetCursor(4, 1);
                        WriteString("IS VALID");
                        HAL_GPIO_TogglePin(GPIOA, LOCK);
                        HAL_Delay(5000);
                        HAL_GPIO_TogglePin(GPIOA, LOCK);
                        Clear();
                    }
                }
                if (!valid_card)
                {
                    STATUS_NOT_OK();
                    Clear();
                    SetCursor(0, 0);
                    WriteString("*SECURITY CARD*");
                    SetCursor(3, 1);
                    WriteString("IS INVALID");
                    ++count_spam;
                    HAL_Delay(1000);
                    if (count_spam == MAX_SPAM)
                    {
                        count_spam = 0;
                        WAIT_TO_SCAN_AGAIN();
                    }
                    Clear();
                }
            }
        }
        if (EnterInterupt)
        {
            EnterInterupt = false;
            if (menu1_status && !(menu2_status))
            {
                menu2_status = true;
                Menu2();
            }
            HAL_Delay(10);
            EXTI->IMR |= (1UL << 12);
        }
        if (DownInterrupt)
        {
            DownInterrupt = false;
            if (menu1_status && !(menu2_status))
            {
                ++dem;
                if (dem > 4)
                    dem = 1;
                Menu1();
            }
            if (menu1_status && menu2_status)
            {
                menu2_status = false;
                Menu1();
            }
            HAL_Delay(10);
            EXTI->IMR |= (1UL << 13);
        }
    }
}
void WAIT_TO_SCAN_AGAIN()
{
    Clear();
    SetCursor(0, 0);
    WriteString("DISABLE SCANNING");
    SetCursor(0, 1);
    WriteString("PLEASE WAIT:");
    for (int count = SECOND_WAIT; count >= 0; --count)
    {
        char lcd_buffer[2];
        sprintf(lcd_buffer, "%02d", count);
        SetCursor(12, 1);
        WriteString(lcd_buffer);
        HAL_Delay(1000);
    }
}
void ConvertFlashValue(uint32_t flashAddress, uint8_t *resultArray)
{
    // Read value from flash
    uint32_t flashValue = Flash_Read_4Byte(flashAddress);
    // Convert flash value to array uint8_t
    for (uint8_t i = 0; i < UID_byte; i++)
    {
        resultArray[i] = (uint8_t)(flashValue >> (8 * i));
    }
}
void Master_Setup_Display(void)
{
    SetCursor(2, 0);
    WriteString("SETUP YOUR");
    SetCursor(2, 1);
    WriteString("MASTER CARD");
}
