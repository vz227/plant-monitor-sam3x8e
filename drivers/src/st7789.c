/** @file st7789.c
 *  @brief Driver for the ST7789 LCD controller.
 *
 *  Contains function implementations from st7789.h
 *
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date August 28, 2026
 */

#include "st7789.h"

static const spi_cfg_t st7789_cfg =
{
    .role = SPI_MASTER,
    .mode = SPI_MODE_0,
    .select_mode = SPI_FIXED_SELECT,
    .chip_select = 0,
    .bits = SPI_BITS_8,
    .mck_divisor = 2
};

static void st7789_reset()
{
    /* Assert RESX */
    delay_ms(64);
    pio_write(PIO_B, RST_PIN, PIO_CLEAR);
    delay_ms(64);
    pio_write(PIO_B, RST_PIN, PIO_SET);
    delay_ms(64);
}

static void st7789_write_cmd(const uint8_t cmd)
{
    pio_write(PIO_B, CS_PIN, PIO_CLEAR);
    pio_write(PIO_B, DC_PIN, PIO_CLEAR);
    spi_transfer(&cmd, NULL, 1, st7789_cfg.bits);
    pio_write(PIO_B, CS_PIN, PIO_SET);
}

static void st7789_write_data(const uint8_t* data, size_t len)
{
    pio_write(PIO_B, CS_PIN, PIO_CLEAR);
    pio_write(PIO_B, DC_PIN, PIO_SET);
    spi_transfer(data, NULL, len, st7789_cfg.bits);
    pio_write(PIO_B, CS_PIN, PIO_SET);
}

void st7789_init()
{
    /* Disable watchdog timer */
    wdt_disable();

    /* Initialize SPI */
    spi_init(&st7789_cfg);

    /* Initialize GPIO */
    pio_init(PIO_B, CS_PIN);
    pio_init(PIO_B, DC_PIN);
    pio_init(PIO_B, RST_PIN);

    /* Perform HW reset */
    st7789_reset();

    /* Perform SW reset */
    st7789_write_cmd(SWRESET);
    delay_ms(5);

    /* Configure row/column addressing order */
    st7789_write_cmd(MADCTL);
    st7789_write_data(madctl_init, sizeof(madctl_init));

    st7789_write_cmd(COLMOD);
    st7789_write_data(colmod_init, sizeof(colmod_init));

    /* Turn on inversion */
    st7789_write_cmd(INVON);

    /* Column & row address windows */
    st7789_write_cmd(CASET);
    st7789_write_data(caset_init, sizeof(caset_init));
    st7789_write_cmd(RASET);
    st7789_write_data(raset_init, sizeof(raset_init));

    /* Porch settings */
    st7789_write_cmd(PORCTRL);
    st7789_write_data(porctrl_init, sizeof(porctrl_init));

    /* Gate control */
    st7789_write_cmd(GCTRL);
    st7789_write_data(gctrl_init, sizeof(gctrl_init));

    /* Common electrode voltage across LCD panel */
    st7789_write_cmd(VCOMS);
    st7789_write_data(vcoms_init, sizeof(vcoms_init));

    st7789_write_cmd(LCMCTRL);
    st7789_write_data(lcmctrl_init, sizeof(lcmctrl_init));

    st7789_write_cmd(VDVVRHEN);
    st7789_write_data(vdvvrhen_init, sizeof(vdvvrhen_init));

    st7789_write_cmd(VRHS);
    st7789_write_data(vrhs_init, sizeof(vrhs_init));

    st7789_write_cmd(VDVSET);
    st7789_write_data(vdvset_init, sizeof(vdvset_init));

    st7789_write_cmd(FRCTRL2);
    st7789_write_data(frctrl2_init, sizeof(frctrl2_init));

    st7789_write_cmd(PWCTRL1);
    st7789_write_data(pwctrl1_init, sizeof(pwctrl1_init));

    st7789_write_cmd(PVGAMCTRL);
    st7789_write_data(pvgamctrl_init, sizeof(pvgamctrl_init));

    st7789_write_cmd(NVGAMCTRL);
    st7789_write_data(nvgamctrl_init, sizeof(nvgamctrl_init));

    st7789_write_cmd(SLPOUT);
    delay_ms(120);

    st7789_write_cmd(DISPON);
    delay_ms(20);
}

static void st7789_set_window(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye)
{
    uint8_t caset_data[] =
    {
        xs >> 8u,
        xs & 0xFF,
        xe >> 8u,
        xe & 0xFF
    };
    uint8_t raset_data[] =
    {
        ys >> 8u,
        ys & 0xFF,
        ye >> 8u,
        ye & 0xFF
    };

    st7789_write_cmd(CASET);
    st7789_write_data(caset_data, sizeof(caset_data));

    st7789_write_cmd(RASET);
    st7789_write_data(raset_data, sizeof(raset_data));

    st7789_write_cmd(RAMWR);
}

void st7789_clear(const uint16_t color)
{
    st7789_set_window(0, DISPLAY_WIDTH - 1, 0, DISPLAY_HEIGHT - 1);

    uint8_t pixel_buffer[DISPLAY_WIDTH * 2u];

    for (size_t i = 0; i < sizeof(pixel_buffer); i += 2 )
    {
        pixel_buffer[i] = color >> 8u;
        pixel_buffer[i+1] = color & 0xFFu;
    }

    for (size_t j = 0; j < DISPLAY_HEIGHT; j++)
        st7789_write_data(pixel_buffer, sizeof(pixel_buffer));
}

void st7789_draw_glyph(const uint16_t xs, const uint16_t ys, const uint16_t glyph_width, const uint16_t glyph_height, const uint16_t fg_color, const uint16_t bg_color, const uint8_t* bitmap_data)
{
    st7789_set_window(xs, (xs + glyph_width) - 1, ys, (ys + glyph_height) - 1);

    uint8_t glyph_buffer[(glyph_width * glyph_height) * 2u];

    for (size_t i = 0; i < glyph_height; i++)
    {
        for (size_t j = 0; j < glyph_width; j++)
        {
            uint16_t color = (bitmap_data[i] & (1u << (7u - j))) ? fg_color : bg_color;
            size_t pixel_index = ((i * glyph_width) + j) * 2u;

            glyph_buffer[pixel_index] = color >> 8u;
            glyph_buffer[pixel_index + 1] = color & 0xFF;
        }
    }

    st7789_write_data(glyph_buffer, sizeof(glyph_buffer));
}
