# TivaC-PWM
<h4>Use the built in timers of the TM4C123GH to create PWM on some of the pins at multiple frequencies and duty cycles</h4>

<p>While PWM is readily available in complete IDEs Enerigia doesn't allow it on the Tiva C Launchpad from Texas Instruments. This code Arduino/Energia code is meant as a hack to allow PWM in a Energia's simplified environment. Set the duty cycle and frequency of multiple pins with this Energia library.</p>

<p>This code is based on a timer hack I found online and uses direct register access to create PWM output. NOT ALL PINS CAN USE THIS INDEPENDENTLY! Some pins use use the same timer and so can't be controlled independently. Please refer to the data sheet or <a href="http://shukra.cedt.iisc.ernet.in/edwiki/EmSys:TM4C123_Use_of_GPTM_with_GPIO_Pins">this webpage</a> for more information about which pins depend on the same timer and cannot have different PWM output.</p>

<p>List of available pins:
  <ul>
    <li>19</li>
    <li>14</li>
    <li>17</li>
    <li>40</li>
    <li>31</li>
    <li>30</li>
    <li>2</li>
    <li>39</li>
    <li>4</li>
    <li>38</li>
  </ul>
    
