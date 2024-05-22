# EPD-UI-Lib

This project provides a library of User Interface (UI) components designed for rendering on E-Paper Displays (EPDs). These components facilitate the development of simple, touch-controlled applications. The library is built upon EPDiy and is primarily coded for the Lilygo T5 4.7" v2.3, which features an Espressif ESP32-S3 microcontroller and a touchscreen layer. Link to a YouTube video showcasing all of the components: https://youtu.be/0oKPSs4F_3k

## 1. Preresiquites

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

## 2. How to install

1. Open **VSCode** and access the **PlatformIO** extension.
2. Navigate to the *Platforms* tab.
3. Choose the *Embedded* tab, then search for and install the **Espressif 32** platform.
4. Clone or download this repository to a local folder on your computer.
5. Within **PlatformIO Home**, select *Open Project*.
6. Browse to the folder containing your repository clone.
7. After the initial PlatformIO setup completes, connect your EPD to your computer via USB.
8. Proceed to build the application.

## 3. How to use

The main.ino file serves as the foundational code for initializing the microcontroller. It includes all of the essential libraries, extensions, handlers, applications and graphical assets such as icons, fonts and UI components. This file executes the setup functions for all handlers, starts necessary tasks, and establishes a Wi-Fi connection. It also synchronizes the current time, initiates connections to the Electronic Paper Display (EPD) and the touch layer, interfaces with external services via Application Programming Interfaces (APIs), generates framebuffers, and finally renders the user interface (UI) of the home screen. Ideally, the loop function should remain empty, to keep the code clean.

The UI is constructed using a modular system of components, including interactive buttons, checkboxes, cards, and many more. These elements are integrated into a framebuffer, which is essentially a memory-stored representation of the screen’s next state. The framebuffer is structured as a two-dimensional array, mirroring the display’s resolution, where each pixel corresponds to a specific shade of gray designated for display at particular coordinates. It accumulates all changes within a single frame, such as the rendering of multiple labels and buttons, and subsequently, the display updates the entire screen with all buffered components at once. This method shortens the time needed for a refresh and reduces the frequency of screen refreshes, minimizing display wear. Interactive elements’ coordinates are stored within a touch handler, which maps the coordinates to their respective components and associated functions. These functions can interact with external APIs, control connected devices, or modify the displayed UI. The touch handler continuously monitors for touch input to facilitate user interaction.

## 4. Components

During the implementation of the user app, components are rendered on the display by calling their respective draw functions. They present essential building blocks needed for the development of a wide array of complex applications. The attributes necessary for the draw functions are provided by the user, consisting of coordinates for component placement, color specifications, typeface, text content, text color, the callback function for button interaction, and the designated framebuffer in which the component should be stored. Typeface selection is specified by the desired size and a boolean value for boldness.

The user assembles the visual layout by gathering various components within a framebuffer. There are multiple framebuffers to help organize the components, the primary framebuffer and those for popups, status bar, and notifications. Components are not rendered instantaneously upon their function call; instead, the user executes a function to collectively render all the contents stored in the framebuffer.

There are two reasons for the usage of the framebuffers. Firstly, it allows for a single screen refresh to render all components at the same time, making the refresh much faster, reducing energy consumption, and minimizing display wear. Secondly, it allows the display of rendering temporary overlays like popups or notifications "above" the previously displayed user interface. After a set period of time, the previous screen state can be restored and displayed again.

Each component’s interaction point is stored within an array of touchpoints, which are continuously monitored for user interaction. The touchpoints are automatically calculated based on the component’s dimensions, with the user only needing to provide the associated callback function. Upon detecting a touch within a component’s designated area, the system triggers the corresponding function based on the touch coordinates and the corresponding component.

Transitioning between screens involves the processes of clearing the framebuffer, filling it with new data, and rendering it to the display.

To enable automatic refreshing of components, they may be encapsulated within an RTOS task.

You can find all components and the design of the example apps in the [Figma EPD UI Library](https://www.figma.com/file/5f3T7Kzn7FPU1AODnGr8Qp/EPD-UI-library?type=design&node-id=11%3A11&mode=design&t=Z7qkNqDndZ23cS3K-1).

### Label

The text drawing on EPDs is facilitated by EPDiy driver. The "writeln" function allows writing a simple line of black text. For advanced typographic attributes and coloration, the "write_mode" function is used. The "write_string" function allows for extensive strings in the composition of multiple lines.

### Button
Interactive elements within the interface include a variety of buttons. The rectangular button serves as the primary interactive element, often rendered with a black background. On the other hand, a white background with a black border designates the button as secondary. These buttons are utilized primarily for approve on cancel actions. Tertiary buttons, without any borders or outlines, are used for non-essential functions. Circular buttons are versatile, supporting both icons and textual labels.

### Card
The card is a component larger than a button, designed for extended textual content. It allows to integrate additional elements, such as icons, labels, or toggles, by overlapping them above the card. This layering enables the creation of application-specific elements. The user need to call "epd_draw_card" first, then call functions that render the additional components.

### Slider
Sliders offer an interactive means to adjust values, typically through the plus or minus symbols within a vertical component. The slider is used in the Homescreen for setting the desired temperature of an air conditioning.

### Toggle
The toggle component functions as a binary switch, enabling users to alter its state by clicking on it. 

### Checkbox
Checkboxes present a multi-selection interface, allowing users to select several options at once. It is recommended to integrate related checkboxes within a card for better differentiation.

### Notification
Notifications serve to inform users of current statuses or errors, accompanied by icons and labels. These alerts appear at the top of the screen, temporarily replacing the status bar for a duration of five seconds.

### Radio button
Radio buttons provide a single-selection interface, ensuring that only one option within a group is active at any given time. Similarly to checkboxes, it is advised to integrate radio buttons within a single card.

### Progressbar
The progress bar visually represents the percentage of a process. It is used in Control panel, where it indicates the water level in coffee machine.

### Pop-up
Pop-up dialogues are multi-line cards that spans across the screen center, featuring a pair of buttons. They are providing additional information user and are used for confirmation of user actions. They are featured as dialogues for new alarm creation or device shutdown confirmation.

### Status bar
The status bar consistently displays the current time and date, refreshing autonomously. It provides navigational shortcuts, allowing users to return to the home screen or access the control panel. It has fixed position at the top of the screen.

### Icons and Images

The icons and images work the same as typefaces. The conversion of these images into a usable format is done by a utility provided by [Lilygo](https://https://github.com/Xinyuan-LilyGO/LilyGo-EPD47/blob/esp32s3/scripts/imgconvert.py). Post-conversion, the icons are stored within an \verb|image| directory. Icons may be included on an individual basis by using the epd_copy_to_framebuffer function or through the icons.h file. It is crucial that the resolution of the converted icons is the same as the desired resolution in which they will be rendered on the display. Typically, icons are rendered at a standard size of approximately 32x32 pixels, whereas icons intended for cards are sized at 64x64 pixels. Transparency in images is not supported; areas intended to be transparent will appear black upon rendering. The icons incorporated into this project are sourced from [Flaticon](https://www.flaticon.com/).

## 5. Example apps
Applications are initially stored to the framebuffer before being rendered on the display with all components at once. Each application features a status bar at the top, providing essential information about time and date, and shortcuts to the Homescreen and Control panel. Applications are bulit of library components, supplemented by labels and basic shapes such as lines and rectangles from the EPDiy driver. Each application has assigned distinct touch points.

### Alarm
The alarm application showcases the potential to combine pre-fabricated cards with other components by overlapping them. By invoking "epd_draw_card" prior to adding icons, labels, and toggles, an integration within the card is achieved, creating unique, application-specific elements.

### Bus departures
This application displays nearest public transport departures from user-defined stops, showing the "write_string" function’s capability to calculate line heights, ensuring separation between distinct lines.

### Control panel
The control panel offers a selection of operations for connected smart home devices, such as coffee machines, window blinds, lights, and speakers. This functionality is demonstrated through the use of radio buttons, checkboxes, progress bars, and pop-up overlays. After the user powers off the device, a persistent fullscreen image is displayed, showing that EPD display remains visible even when the device is disconnected from the grid.

### Homescreen
The home screen allows users to create shortcuts to frequently used utilities, such as air conditioning controller (slider component), light switch (toggle component), or door lock (triggering notification). Application shortcuts provide a quick glance of current information, such as the currently playing song on Spotify or the outdoor temperature on a Weather card. At the lesft side, self-refreshing clock is also displayed.

### Spotify
The Spotify application interfaces with the Spotify API to control playback using circular and tertiary buttons, and displaying information about the currently playing track. Track information updates are managed by the "updateCurrentlyPlaying" function within spotify_handler.cpp, which is routinely invoked by a background RTOS task initiated during the Spotify setup.

### Weather
This application illustrates multiple screens within a single app, navigable via tertiary buttons beneath the status bar. The primary screen presents current weather information within nine cards, with icons reflecting current weather conditions. Additional screens provide forecasts for the upcoming three hours and three days, with data sourced from the OpenWeather OneCall 3.0 API.

## 6. Handlers

Detailed information regarding handlers is accessible within the appropriate header files in the source code.

### EPD handler
The EPD handler extends the scope of the EPDiy driver functions. While the EPDiy driver lays the foundation with basic functions for storing various objects to the framebuffer and subsequent display rendering, the EPD handler builds upon this, offering functions for display initialisation, sleep mode activation, rounded rectangle drawing, display preparation for showing a new screen, and sequential framebuffer rendering to prevent artifact formation during simultaneous drawing on two distinct screen regions.

### Framebuffer handler
The framebuffer handler is designed to initialize framebuffers, facilitate their clearance, and provide getter functions for three distinct framebuffers: the main, notification, and overlay buffer.

### Spotify handler
The Spotify handler’s function is to instantiate a Spotify Agent and establish connectivity with Spotify’s servers through their developer API. It initiates a task that periodically refreshes the data regarding the currently playing track, stores this information in a local data structure, and sets a trigger that a new track information was fetched. This handler provides access to track details and the Spotify agent, enabling playback control.

### Time handler
The time handler is responsible for configuring the DHCP connection to the NTP server, which is then utilized to obtain and parse the current time and date into getter functions.

### Touch handler
The touch handler’s role is to initialize the touch interface, create a structure for touch point coordinates and their associated function callbacks, and manage the transition between touch points in the main and overlay framebuffers. Additionally, it provides a dummyFunction, which serves as a placeholder for buttons or cards without assigned functions.

### Weather hanlder
This handler establishes communication with the OpenWeather OneCall 3.0 API, retrieves current weather conditions, and forecasts for the next three hours and three days. Although the service necessitates a subscription, 1 000 free calls are available daily. The fetched data is stored in a structured format with getter functions.

### WiFi handler
The Wi-Fi handler enables the device to connect to a Wi-Fi network using credentials specified in the credentials.h file.

## 7. Constants
Incorporating all constants at the project’s start is recommended. These header files provide simle access to frequently used constants, such as dimensions, fonts, colors, and access tokens for Wi-Fi and associated services. Constants enhance code readability and comprehension, allowing for easy size and design adjustments across all component instances at once, which is particularly beneficial when adapting to different display resolutions or evolving the design language.

### Colors
The color header defines a palette of three colors, as there is no need to use more shades of gray in EPD interfaces. However, it is designed to be easily extensible to support color displays. When employing EPDiy functions like "epd_draw_rect" or "epd_draw_circle", a color range conversion through "epd_convert_color_range" function from 0-15 (used by library components and text) to 0-255 (used by EPDiy draw and fill functions) is necessary. Black indicates primary interactive elements, white is used for backgrounds and secondary elements, and gray signifies inactive or deactivated components.

### Components
The components header includes all components and their standardized dimensions. Users have the flexibility to modify these dimensions or introduce new forms for existing elements, such as varying button sizes.

### Credentials
The credentials header stores sensitive user information, including passwords and tokens. This information must remain confidential and cannot be committed to public repositories to prevent unauthorized access. Detailed guidance on acquiring tokens for Spotify and OpenWeather API is provided within the "credentials.c" file.

### Fonts
The fonts header includes a variety of OpenSans fonts in multiple sizes and weights. Functions are available to retrieve the GFXfont object for a desired font size and the dimensions of text intended for drawing. Recommended font usage varies by component, with specific fonts designated for buttons ("TEXT_FONT_BOLD"), circle buttons ("HEADLINE_FONT"), cards ("TITLE_FONT"), and other elements.

If the user wants to use other fonts then the included OpenSans one, they must be converted to a fonts.h format. The conversion is done by a utility tool available on [Lilygo's GitHub repository](https://github.com/Xinyuan-LilyGO/LilyGo-EPD47/blob/esp32s3/scripts/fontconvert.py). This representation supports the entire basic ASCII character set, including a set of emojis.
