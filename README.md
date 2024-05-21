# EPD-UI-Lib

This project provides a library of User Interface (UI) components designed for rendering on E-Paper Displays (EPDs). These components facilitate the development of simple, touch-controlled applications. The library is built upon EPDiy and is primarily coded for the Lilygo T5 4.7" v2.3, which features an Espressif ESP32-S3 microcontroller and a touchscreen layer. Link to a YouTube video showcasing all of the components: https://youtu.be/0oKPSs4F_3k

## Preresiquites

* [Lilygo T5 4,7 EPD](https://www.lilygo.cc/products/t5-4-7-inch-e-paper-v2-3) or any other [EPDiy](https://github.com/vroland/epdiy) supported display
* [Touchscreen layer](https://www.lilygo.cc/products/t5-4-7-inch-e-paper-1?variant=42450586140853) for Lilygo T5
* [Visual Studio Code](https://code.visualstudio.com/) with [PlatformIO IDE extension](https://platformio.org/platformio-ide) installed
* [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) installed
* Dependency libraries (should be added automatically by PlatformIO)
  * [PCF8563\_Library](https://github.com/lewisxhe/PCF8563_Library)
  * [LilyGoEPD47](https://github.com/Xinyuan-LilyGO/LilyGo-EPD47)
  * [Arduino/Wire](https://github.com/esp8266/Arduino/tree/master/libraries/Wire)
  * [SpotifyArduino](https://github.com/witnessmenow/spotify-api-arduino)
  * [OpenWeather](https://github.com/Bodmer/OpenWeather)
  * [EPDiy](https://github.com/vroland/epdiy}{github.com/vroland/epdiy)

## How to install

1. Open **VSCode** and access the **PlatformIO** extension.
2. Navigate to the *Platforms* tab.
3. Choose the *Embedded* tab, then search for and install the **Espressif 32** platform.
4. Clone or download this repository to a local folder on your computer.
5. Within **PlatformIO Home**, select *Open Project*.
6. Browse to the folder containing your repository clone.
7. After the initial PlatformIO setup completes, connect your EPD to your computer via USB.
8. Proceed to build the application.

## How to use

The main.ino file serves as the foundational code for initializing the microcontroller. It includes all of the essential libraries, extensions, handlers, applications and graphical assets such as icons, fonts and UI components. This file executes the setup functions for all handlers, starts necessary tasks, and establishes a Wi-Fi connection. It also synchronizes the current time, initiates connections to the Electronic Paper Display (EPD) and the touch layer, interfaces with external services via Application Programming Interfaces (APIs), generates framebuffers, and finally renders the user interface (UI) of the home screen. Ideally, the loop function should remain empty, to keep the code clean.

The UI is constructed using a modular system of components, including interactive buttons, checkboxes, cards, and many more. These elements are integrated into a framebuffer, which is essentially a memory-stored representation of the screen’s next state. The framebuffer is structured as a two-dimensional array, mirroring the display’s resolution, where each pixel corresponds to a specific shade of gray designated for display at particular coordinates. It accumulates all changes within a single frame, such as the rendering of multiple labels and buttons, and subsequently, the display updates the entire screen with all buffered components at once. This method shortens the time needed for a refresh and reduces the frequency of screen refreshes, minimizing display wear. Interactive elements’ coordinates are stored within a touch handler, which maps the coordinates to their respective components and associated functions. These functions can interact with external APIs, control connected devices, or modify the displayed UI. The touch handler continuously monitors for touch input to facilitate user interaction.

## Components

During the implementation of the user app, components are rendered on the display by calling their respective draw functions. They present essential building blocks needed for the development of a wide array of complex applications. The attributes necessary for the draw functions are provided by the user, consisting of coordinates for component placement, color specifications, typeface, text content, text color, the callback function for button interaction, and the designated framebuffer in which the component should be stored. Typeface selection is specified by the desired size and a boolean value for boldness.

The user assembles the visual layout by gathering various components within a framebuffer. There are multiple framebuffers to help organize the components, the primary framebuffer and those for popups, status bar, and notifications. Components are not rendered instantaneously upon their function call; instead, the user executes a function to collectively render all the contents stored in the framebuffer.

There are two reasons for the usage of the framebuffers. Firstly, it allows for a single screen refresh to render all components at the same time, making the refresh much faster, reducing energy consumption, and minimizing display wear. Secondly, it allows the display of rendering temporary overlays like popups or notifications "above" the previously displayed user interface. After a set period of time, the previous screen state can be restored and displayed again.

Each component’s interaction point is stored within an array of touchpoints, which are continuously monitored for user interaction. The touchpoints are automatically calculated based on the component’s dimensions, with the user only needing to provide the associated callback function. Upon detecting a touch within a component’s designated area, the system triggers the corresponding function based on the touch coordinates and the corresponding component.

Transitioning between screens involves the processes of clearing the framebuffer, filling it with new data, and rendering it to the display.

To enable automatic refreshing of components, they may be encapsulated within an RTOS task.

You can find all components and the design of the example apps in the [Figma EPD UI Library](https://www.figma.com/file/5f3T7Kzn7FPU1AODnGr8Qp/EPD-UI-library?type=design&node-id=11%3A11&mode=design&t=Z7qkNqDndZ23cS3K-1).

### Label

Labels are provided by the EPDiy library. The user can use "writeln" function for writing a simple line of black text,
"write_mode" for more advanced font properties and colors, or "write_string" for writing a simple multiple lines of a long string.<br/>

### Button
There are several buttons: rectangular one which can be used as primary when its backgorund color is black, or secondary, when its color is white - in that case there is a black border around the white button. These buttons are used primarily for approving on cancelling. Tertiary buttons have no border or outline and are used for additional, non-essential functions. Circle buttons can be used with icon or with a label.  


<br/>

### Card
The card is used to provide an information. It is bigger than a button and provides more lines of text. The user can integrate other components into the card by drawing them atop of the card. The components can overlap themselves so the user can draw icons, labels or toggles atop of the card in order to integrate them into the card and create his own app-specific elements. In order to visually "integrate" them into the card, the user just needs to call epd_draw_card first and then other functions that will draw other components atop of the card. In this way, the user can create his own app-specific elements.

<br/>

### Slider

The user can change the value by clicking on the plus or minus symbol inside a vertical component.  The slider is used in the AC controller app for setting the desired temperature.

<br/>

### Toggle

Serves as an on/off switch. The user can change the state of the toggle by clicking on it. 

<br/>

### Checkbox

Provides a multi-choice selection interface as the user can select multiple checkboxes at once. Should be integrated into a card with all other connected checkboxes. 

<br/>

### Notification
Provides an current information about status or error with an icon and label. For 5 seconds shows at the top of the screan instead of a Status bar.

<br/>

### Radiobutton

Provides a single-choice selection interface. Should be integrated into a card with all other connected radio buttons.

<br/>

### Progressbar

Serves as an indicator of a percentage of a process in a line. It is used in COntrol panel for displaying the Coffee machine water level.

### Popup
This is a multiline card spanned across the center of the screen with two buttons. It is used for additional information or for a confirmation of an action. It is used for example in the Alarm app when the user wants to add a new alarm or in the Control panel when the user wants to turn off the device.
<br/>

### Status bar

Status bar has a self-refreshing time and date and provides a way to get back to the Homescreen or  a quick way to get to the Control Panel. It is always at the top of the screen. 

### Icons and Images

The icons and images work the same as typefaces. The conversion of these images into a usable format is done by a utility provided by [Lilygo](https://https://github.com/Xinyuan-LilyGO/LilyGo-EPD47/blob/esp32s3/scripts/imgconvert.py). Post-conversion, the icons are stored within an \verb|image| directory. Icons may be included on an individual basis by using the epd_copy_to_framebuffer function or through the icons.h file. It is crucial that the resolution of the converted icons is the same as the desired resolution in which they will be rendered on the display. Typically, icons are rendered at a standard size of approximately 32x32 pixels, whereas icons intended for cards are sized at 64x64 pixels. Transparency in images is not supported; areas intended to be transparent will appear black upon rendering. The icons incorporated into this project are sourced from [Flaticon](https://www.flaticon.com/).

## Example apps

Each app is firstly completely stored to the framebuffer and then drawn on the display at once. Each app has an Status bar with a Control panel at the top of the screen so the user can get back to the Homescreen and has basic information in front of his eyes at all times. Every app consists only from components from this library and then from labels from font.h and basic objects such as lines and rectangles from EPDiy driver. Every app has its own touch layer. Icons are from Flaticon.

### Alarm

The alarm app demonstrates the possibility to combine premade cards with other components by overlaping. Above the cards there are icons, labels and toggles. In order to visually "integrate" them into the card, the user just needs to call epd_draw_card first and then other functions that will draw other components atop of the card. In this way, the user can create his own app-specific elements.

After clicking the plus button, a popup overlay opens. In the same way it uses the overlay that consists of a card expanded to the whole screen and overlapped with various additional radio buttons, checkboxes and a numeric keyboard.

### Bus departures

Simple app showing nearest departures of public transport from user defined stops. Showcases "write string" function in which it handles computing of a height of the line all by itself so the next line is nicely below without ovelaping.

### Control panel

In the control panel there are multiple choices on how to operate the connected smart home appliances like coffee machine, window blinds, lights and speakers. This is showcased by the usage of radiobuttons, checkboxes, progressbar and again, an overlay popup that asks the user wheter they want to turn off the device. After that, there will be displayed a fullscreen image that will be persistent on the display even when powered off and unplugged from the grid (thanks to EPD technology).

### Homescreen

Here, the user can create shortcuts to the most used utilities. For example AC controller (slider component), lights switch (toggle component) or door lock (triggers a notification). Shortcuts to apps provide a quick glance to current info. For example Spotify card shows the name of the current playing song and Weather card shows the current outside temperature. It is also displaying big self-refreshing clock.

### Spotify

Via Spotify API controls the playback using circle and tertiary buttons, and shows information about currently playing track. The track information is being updated by a updateCurrentlyPlaying function in the spotify_handler.cpp. This function is regularly called by a background RTOS task created during the spotifySetup.

### Weather

This app demonstrates several screens within one app between which the user can switch by tertiary buttons below the status bar. The first screen shows information about the currents whether inside of 9 cards with icons changing based on the current weather status. Other two screens are showing information about forecast for nearest 3 hours and 3 days. The information is pulled from OpenWeather OneCall 3.0 API.

## Handlers

All detailed information can be found in the appropiate header files in the source code.

### EPD handler

This handler extends the scope of the EPDiy driver functions. Additionaly to the EPDiy driver, it supports rounded rectangles. While EPDriver provides basic functions to store various objects (rectangles, lines, circles, images, text) to the framebuffer and later to draw on the screen, and clearing the display, this EPD handler builds upon that. It provides functions for setting up the display, setting the display into sleep mode, drawing rectangles with rounded corners, settig up the display for displaying a new screen and drawing framebuffers sequentially in order to avoid display artefacts creation when drawing simuntaneously on two distinct places.

### Framebuffer handler

Provides functions for setting up the framebuffers, clearing them and it also provides getter functions for all three framebuffers - main, notification and overlay.

### Spotify handler

Its role is to create an instance of a Spotify Agent and setup the connection with Spotify servers via their developer API. This process is by a code from Brian Lough (link footnote). It creates a task that repeatedly updates the information about the currently played track, saves the information into the local data structure and sets a trigger that a new track information was fetched. Provides an access to the track information and to the Spotify agent though which the user can access the playback control functions.

### Time handler

Provides functions to set up the DHCP connection to the NTP server, from which the current time and dite is then fetched and parsed into a getter functions.

### Touch handler

Provides functions to innitialize the touch layer, create a structure to store all of the touch point coordinate and their corresponding function callbacks. It also manages the switching from touch points in main framebuffer and touchpoints in the overlay framebuffer. Provides also a dummyFunction that does nothing and can be passed as an argument to the buttons or cards without any function.

### Weather hanlder

This handler sets up the communication with the OpenWeather Onecal 3.0 API, fetches the current weather and forecast for next three hours and three days. This service requires a subscription (however 1000 calls per day are free). All of this information it stores to the structure and provides getter functions.

### WiFi handler

It allows the device to connect to a WiFi with user-defined credentials stored in the credentials.h.

## Constants

Best to include all four at the start of the project. All of these headers files provide easier way to access commonly used constants in which there are stored various dimensions, all of the fonts, colors and access tokens to WiFi and connected services. Thanks to constants, not only the code is much more readable and easier to understand, but the main thing is that by change of the constant the user can change design and sizes of the all of the instances of the components at once, which is nice, for example, when using the library on a display with a different resolution or adapting the design to newer design languages.

### Colors

In Colors there are only 3 colors because in the UI for grayscale EPD there is no need to use more shades of gray. However it is easily extensible by other colors when using color display for example. Specificaly when using EPDiy functions such as epd_draw_rect or epd_draw_circle, you need to convert the color range from 0-15 as used with library components or drawing text but to range 0-255 which is used by the EPDiy library. For this the user can use simple conversion function epd_convert_color_range. The black color is used for main interactive elements, primarily for buttons and cards with binded functions. White color is used for backgrounds, un-interactive cards that only serves as information provider and for secondary and tertiary buttons. The gray color is used only for inactive elements or elements that are switched off.

### Components

There are included all components and all standardised dimensions for them. The user can of course, change them to make the components bigger or smaller, or add new set of dimensions for the existing elements (somtehing like big button or small button).

### Credentials

There are stored local information about the user, such as passwords, tokens and location of the device. These needs to be stored only localy and cannot be commited to any public repository, otherwise the users credential can be vulnerable and stolen. In credentials.c file there is detailed information on how to get the tokens for Spotify and OpenWeather API.

### Fonts

There are all imported OpenSans fonts in various sizes and even in bold variants. There is a function that return the GFXfont object of the requested font size. There is also a function to get the dimensions of the text the user might want to draw on the display. For buttons it is recommended to use TEXT_FONT, for circle button TITLE_FONT, for cards xxpx and for other elements xxpx.

If the user wants to use other fonts then the included OpenSans one, they must be converted to a fonts.h format. The conversion is done by a utility tool available on [Lilygo's GitHub repository](https://github.com/Xinyuan-LilyGO/LilyGo-EPD47/blob/esp32s3/scripts/fontconvert.py). This representation supports the entire basic ASCII character set, including a set of emojis.
