# The Ultimate Drinks Machine! 🍹🚀

🍸 Have you ever wanted a drink, but didn't want to spend the time making it? Then this machine is for you! Simply, order it through the user friendly UI on the embedded touch screen of the machine. Worried about running out of supplies? Don't worry! The machine keeps track of how much is used, and reaches out to you when it is time to order more drink supplies!

🤯 Through our revolutionary ConfigUI® you can even adjust the ratios of the drinks, create your own drinks to your heart's desire or review some worrying statistics about your alcohol consumption.

🛠️ All this, and much more is included in this bundle deal of a machine. Unfortunately, this machine is out of stock for ordering, but follow the documentation and you might just be able to build it yourself! :)

## Formal introduction and requirements

This repository reflects the work on the third semester project in Software Technology at Aarhus University - Department of Electrical & Computer Engineering. The project has a few requirements, namely that our system needs to interact with the physical world through sensors and actuators. More over, we are required to develop the software for the required CPUs, namely a [PSoC 5](https://www.infineon.com/cms/en/product/microcontroller/32-bit-psoc-arm-cortex-microcontroller/32-bit-psoc-5-lp-arm-cortex-m3/) microcontroller and an embedded linux platform, which for us is a [Raspberry Pi 4 B](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/). Also, some kind of graphical user interface (GUI) is required.

## Process of developement

We are implementing SCRUM principles for controlling the development process for the project, which is part of the formal process requirements.

The sprints can be seen in the Trello pages below:

- [Early implementation and stabilisation of requirements](https://trello.com/b/BRn3iF2r/tidlig-implementering-og-stabilisering-af-krav-2-uger)

## This is a mono repository

For this project, we have chosen a mono repo structure as this has a few benefits for us:

- Easier to quickly browse our codebase in one place
- Managing one repo is easier than multiple
- Makes it easier to share code between CPUs and platforms

## Table of contents

In this repo we have the following folder structure:

- `docs`
  represents different types of documentation of the project.
- `source`
  contains the source code for the project. Subfolders should contain code for specific parts of the project and a README, which reflects purpose and functionality
- `prototyping`
  is for experimenting with different technologies. Each subfolder should represent a single self contained experiment, which means it can include code for muliple CPUs and platforms. Can contain a README with a description and instructions as to how the experiment can be executed.
