#pragma once
#include <halpp/system.hpp>
#include <stdint.h>
namespace hal::detail
{
#if defined(STM32F1)
    template<typename T1, typename T2>
    inline constexpr uint32_t offset_of(T1 T2::*member)
    {
        constexpr T2 object{};
        return size_t(&(object.*member)) - size_t(&object);
    }

    constexpr static uint32_t GPIO_RCC_EBB = RCC_APB2ENR_IOPAEN;

    template<char PortName>
    constexpr uint32_t GPIO_RCC_EMASK = GPIO_RCC_EBB << (PortName - 'A');

    template<char PortName>
    constexpr uint32_t GPIO_ADDR = GPIOA_BASE + 0x400 * (PortName - 'A');

    template<typename ...>
    using void_t = void;

    enum class pin_mode
    {
        INPUT_ANALOG = 0x0,
        OUT_10M= 0x1,
        OUT = 0x2,
        OUT_50M = 0x3,
        INPUT = 0x4,
        OUT_OPEN_DRAIN_10M= 0x5,
        OUT_OPEN_DRAIN = 0x6,
        OUT_OPEN_DRAIN_50M = 0x7,
        INPUT_PULLDOWN = 0x8,
        AFO_10M = 0x9,
        AFO = 0xA,
        AFO_50M = 0xB,
        INPUT_PULLUP = 0xC,
        AFO_OPEN_DRAIN_10M = 0xD,
        AFO_OPEN_DRAIN = 0xE,
        AFO_OPEN_DRAIN_50M = 0xF
    };

    class pin_base;
#elif defined(__AVR_ARCH__)
    struct GPIO_TypeDef
    {
        register_t* PORT;
        register_t* DDR;
        register_t* PIN;
    };

    template<char, typename T = void_t<> >
    GPIO_TypeDef port = (typename T::nonexistent_gpio_port)();

    #ifdef DDRA
        #define HALPP_PORT_NAME A
        #include <halpp/avr/gpio_typedef_template.h>
    #endif

    #ifdef DDRB
        #define HALPP_PORT_NAME B
        #include <halpp/avr/gpio_typedef_template.h>
    #endif

    #ifdef DDRC
        #define HALPP_PORT_NAME C
        #include <halpp/avr/gpio_typedef_template.h>
    #endif

    #ifdef DDRD
        #define HALPP_PORT_NAME D
        #include <halpp/avr/gpio_typedef_template.h>
    #endif

    #error AVR support is not implemented yet

    // TODO
#endif
}