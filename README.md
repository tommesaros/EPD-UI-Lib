# EPD-UI-Lib

This project provides a library of User Interface (UI) components designed for rendering on E-Paper Displays (EPDs). These components facilitate the development of simple, touch-controlled applications. The library is built upon EPDiy and is primarily coded for the Lilygo T5 4.7" v2.3, which features an Espressif ESP32-S3 microcontroller and a touchscreen layer.

## Preresiquites

* [Lilygo T5 4,7 EPD](https://www.lilygo.cc/products/t5-4-7-inch-e-paper-v2-3) or any other [EPDiy](https://github.com/vroland/epdiy) supported display
* [Touchscreen layer](https://www.lilygo.cc/products/t5-4-7-inch-e-paper-1?variant=42450586140853) for Lilygo T5
* [Visual Studio Code](https://code.visualstudio.com/) with [PlatformIO IDE extension](https://platformio.org/platformio-ide) installed
* [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) installed
* Dependency libraries (should be added automatically by PlatformIO)
  * [PCF8563\_Library](https://github.com/lewisxhe/PCF8563_Library)
  * [LilyGoEPD47](https://github.com/Xinyuan-LilyGO/LilyGo-EPD47)
  * [Arduino/Wire]([https://github.com/Xinyuan-LilyGO/LilyGo-EPD47](https://github.com/esp8266/Arduino/tree/master/libraries/Wire)https://github.com/Xinyuan-LilyGO/LilyGo-EPD47)

## How to install

1. Open **VSCode** and access the **PlatformIO** extension.
2. Navigate to the *Platforms* tab.
3. Choose the *Embedded* tab, then search for and install the **Espressif 32** platform.
4. Clone or download this repository to a local folder on your computer.
5. Within **PlatformIO Home**, select *Open Project*.
6. Browse to the folder containing your repository clone.
7. After the initial PlatformIO setup completes, connect your EPD to your computer via USB.
8. Proceed to build the application.

#TODO pictures

## How to use

#TODO either edit example or create new file in src folder, then use Components by adding "draw_component" method to your code

## Components

You can find all components and the design of the example apps here: [Figma EPD UI Library](https://www.figma.com/file/5f3T7Kzn7FPU1AODnGr8Qp/EPD-UI-library?type=design&node-id=11%3A11&mode=design&t=Z7qkNqDndZ23cS3K-1).

### Label

#TODO pictures, description, attributes to the method, method itself

### Button

#### Primary

```c
draw_primary_button(position_x, position_y)
```

#### Secondary

```c
draw_primary_button(position_x, position_y)
```

#### Ternary

```c
draw_primary_button(position_x, position_y)
```

<br/>

### Icon


<br/>


### Card

#### Small

Picture and desc here

#### Medium

#### Big


<br/>


### Slider


<br/>


### Toggle


<br/>


### Checkbox

<br/>


### Radiobutton

<br/>


### Progressbar

<br/>


### Loading animation

<br/>


### Scrollable list

<br/>


### Notification toast

<br/>


### Status bar

## Examples

#TODO Clock app
