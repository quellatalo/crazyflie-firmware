#include "FreeRTOS.h"
#include "task.h"

#include "config.h"
#include "deck.h"
#include "system.h"

#include "nin.h"

static bool isInit;

void ninInit(DeckInfo* info)
{
    if (isInit)
        return;
    
    pinMode(DECK_GPIO_IO2, OUTPUT);     // Set my Led pin to output
    
    
    xTaskCreate(ninTask, "NIN", configMINIMAL_STACK_SIZE, NULL, 4, NULL);
    
    isInit = true;
}

bool ninTest(void)
{
    if (!isInit)
        return false;
    
    return true;
}

void ninTask(void* arg)
{
    TickType_t lastWakeTime;
    
    systemWaitStart();
    
    lastWakeTime = xTaskGetTickCount();
    
    while (1) {
        vTaskDelayUntil(&lastWakeTime, M2T(50));
        digitalWrite(DECK_GPIO_IO2, HIGH);  // Light it up
        
        vTaskDelayUntil(&lastWakeTime, M2T(50));
        digitalWrite(DECK_GPIO_IO2, LOW);  // Turn it off
        
    }
}

static const DeckDriver nin_deck = {
    .vid = 0,
    .pid = 0,
    .name = "qNin",
    .usedGpio =
    //    DECK_USING_RX1 |
    //    DECK_USING_TX1 |
    //    DECK_USING_SDA |
    //    DECK_USING_SCL |
    //    DECK_USING_IO_1 |
    DECK_USING_IO_2,
    //    |
    //    DECK_USING_IO_3 |
    //    DECK_USING_IO_4 |
    //    DECK_USING_TX2 |
    //    DECK_USING_RX2 |
    //    DECK_USING_SCK |
    //    DECK_USING_MISO |
    //    DECK_USING_MOSI,
    
    .init = ninInit,
    .test = ninTest,
};

DECK_DRIVER(nin_deck);
