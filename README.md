# Pokéwalker Reverse Engineering Personal Project

The Pokéwalker was a specialized, pedometer-shaped accessory released alongside Pokémon HeartGold and SoulSilver for the Nintendo DS. It allowed players to transfer a Pokémon from their game onto the device via infrared (IR) communication, walk around in the real world to earn steps, and use those steps as in-game currency ("Watts") to catch wild Pokémon, find items, and level up their partner before syncing the data back to the console.

This project focuses on designing and prototyping a custom, handheld Pokéwalker accessory centered around an ESP32 microcontroller. The primary goal is to replicate the core functions of the original hardware. This includes wireless data transfer, activity tracking, and interactive user controls within a standalone, battery-powered embedded system.

So far I have focused on implementing short-range infrared data transfer. Using an IrDA 4 Click transceiver module interfaced with the ESP32, initial hardware successfully established raw byte-level transmission and reception. Following signal verification, an optical loopback test was performed using a mirror to confirm that sent data was correct and uncorrupted.

With the foundational IrDA transceiver logic verified, upcoming development will focus on integrating peripheral hardware into a cohesive handheld unit:

Interactive Display: An integrated screen to render menus, status indicators, and gameplay.

IMU Sensor: Sensor integration to track physical motion and step counts.

User Input Controls: Physical pushbuttons for menu navigation and user interaction.

Power Subsystem: Dedicated battery to run low powered functions continuously.


## The 4Cs of Creativity

Mini-c (Personal Learning & Internal Insights): Mini-c represents the personally meaningful interpretations that occur during the learning process. In this project, mini-c manifested when initially analyzing the original accessory's IR protocol and translating raw signal behaviors into actionable embedded software code. Deciphering the byte-level logic and setting up the IrDA 4 Click transceiver module with an optical loopback test provided personal insights into how the IR transceiver works.

Little-c (Everyday Creative Expression & Open-Source Artifact): Little-c reflects everyday creative activities and tangible outputs shared within a social context. Transforming initial hardware testing into a fully functional, documented GitHub repository represents a little-c contribution. Having a GitHub repository that others can see means that my work is open-source; this means that others have the opportunity to look at what I've made, and apply it to their own projects.

Pro-c (Professional Expertise & Domain Integration): Pro-c is the effortful progression toward professional-level expertise within a specific domain. Creating custom firmware, power subsystems, and low-level hardware integration applies engineering principles in embedded systems design. While not changing of the entire microelectronics industry (Big-C), completing this project with consumer level products like an ESP32 microcontroller sits the project between hobbyist and professional engineering practice.

Big-C (Eminent Historical Impact): Big-C is reserved for legendary or historical accomplishments that permanently alter a domain. The original Nintendo Pokéwalker accessory achieved massive commercial reach upon its initial release, but this personal prototype serves as an exploratory engineering exercise rather than an attempt at commercial success or historical remembrance.
