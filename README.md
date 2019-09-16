<p align="right"><img src="https://github.com/BadenLab/Zebrafish-visual-space-model/blob/master/Images/Logo.png" width="300"/>
<h1 align="center">Multi-Chromatic Stimulator</h1></p>
<h4 align="center">An OpenSource LED stimulator for visual and optogenetics stimulation in combination with 2-photon recording</h4>
<p align="center"><h6 align="right">by M.J.Y. Zimmermann, A.M. Chagas, P. Bartel, T. Baden</h6></p>

This project is licensed under the [GNU General Public License v3.0](https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/LICENSE)


The study of colour vision with fluorescence microscopy requires precise control over the spectra of visual stimuli.

Here we describe an effective, low-cost, opensource LED stimulator, designed to be used in combination with a 2-photon microscope. The design is built around an open-source development board and off-the-shelf components. It has been conceived to be assembled and used without the need for advanced electronics skills.


[Instruction Manual](https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/tree/master/Manuscript%20and%20Instruction%20Manual)

***

The following design can control up to 24 spectral channels with 12 bits  linear  resolution and 25 μs temporal precision. Our system only requires simple electronics components to be assemble and can be combined.

<img align="center" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/Stimulator.png" width="1000"/>

***

The stimulator synchronises the light stimulation with the sample scanning in order to prevent interferences with the light emitting probe recording.

<img align="center" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/Blanking.png" width="1000"/>

***

The following design was adjusted for the tetrachromatic zebrafish.
Stimulating LEDs and optical filters were chosen to match the peak sensitivities of opsin spectra while avoiding overlap with the PMT detection bands.

<img align="center" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/Spectra.png" width="1000"/>

***

In this example, the light sources are combined and directed through the onjective.

<img align="center" src="https://github.com/MaxZimmer/Multi-Chromatic-Stimulator/blob/master/Images/Schematics.png" width="1000"/>
