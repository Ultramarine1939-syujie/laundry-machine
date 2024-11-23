# 全自动洗衣机控制系统的设计与实现（auto-laundry-machine）

合肥工业大学-电子工程师课设

## 1、绪论：

洗衣机是现代家庭必不可少的家电，其发明和使用大大节省了人们的洗衣时间与精力，缓解了家务劳动的压力。随着人们对生活质量的不断追求，普通洗衣机已经无法满足部分用户的需求，因此研究多功能全自动洗衣机显得尤为重要。当前，全自动洗衣机因其对衣物磨损小、洗涤容量大、节水等特点，越来越受到大家庭的喜爱。随着社会进步和生活水平的提高，人们对全自动洗衣机的功能多样性和操作简便性提出了更高要求。为了适应这种变化，全自动洗衣机的控制系统也逐渐从机械式和混合式转向全电子控制。

单片机，也称为微控制器或嵌入式控制器，是现代智能家电中普遍使用的核心部件。家用电器是单片机应用最广泛的领域之一，它们在智能化过程中充当着“心脏”和“大脑”。由于家用电器体积较小，因此对控制器的体积也有更高要求，以便能够嵌入设备内部。同时，家用电器种类繁多、功能差异显著，这就要求控制器具备灵活的控制能力。单片机以其小巧的体积和编程灵活性，能够实现多种控制功能，完全满足家用电器的需求。

单片机的独特结构决定了它具有一系列优点，如高集成度、控制功能强、低电压低功耗、性价比极高等。综合来看，基于单片机的自动洗衣机控制系统具有高精度、强功能和良好的经济性。无论是在提升产品质量和数量、节约能源，还是改善劳动条件等方面，都展现出显著优势。

目前，绝大多数洗衣机都采用单片机来控制电机的驱动。通过对微处理器的编程，可以实现显示切换、洗涤、漂洗和脱水的自动转换。同时，优化洗衣机的结构和程序设置，可以有效控制洗衣水流，以满足用户对不同衣物质地和污垢程度的洗涤需求。洗衣机的发展日益成熟，更加人性化。

随着当下用户需求的不断提高，洗衣机的功能变得更加多样化，包括模糊称重、掉电记忆等多种功能，使得洗衣机更贴近用户的需求。目前，中国洗衣机市场正处于更新换代期，市场潜力巨大，但现有洗衣机在许多方面尚未满足人们的要求。这对设计者提出了更高的专业和技术要求，需要他们能够提供更多的建议和新的课题，将用户的需求转化为现实，设计出更节能、功能全面且人性化的全自动洗衣机。因此，对全自动洗衣机控制系统的设计与实现进行深入研究具有重要意义。

## 2、系统方案原理及功能要求

### **2.1 系统方案**

本设计以STM32F103ZET6单片机为核心，基于普中玄武F103开发板进行开发，通过结合步进电机、键盘输入、红外接收模块、RGB彩灯和TFT LCD显示模块，构建了一套全自动洗衣机控制系统。

### **2.2 功能要求**

（1）可设置至少4种不同的洗衣方式，用直流电机或步进电机的转速表示；

（2）通过按键预设不同材质衣服的洗涤方式；

（3）设置开始和暂停，并将洗衣、洗涤方式通过12864或者TFT彩屏显示；

（4）实现定时和预约洗衣的功能，完成洗衣服后，蜂鸣器提示；

（5）通过A/D模块模拟衣物重量，超重提示.

### **2.3 总体设计框图**

全自动洗衣机控制系统设计方案如框图所示，系统以STM32F103ZET6为核心，外围配置了TFT LCD显示模块、RGB彩灯矩阵模块、RTC定时模块、蜂鸣器发声模块、步进电机驱动模块、红外接收模块等外设。系统的主要工作流程如下：

工作启停按钮按下，单片机识别后蜂鸣器发声，随后启动电机驱动模块，按照预设模式进行洗衣作业；

更换模式按钮按下，单片机识别后蜂鸣器发声，修改洗衣模式，并更改LCD显示屏的洗衣模式显示，同时RGB彩灯矩阵更换不同的颜色以表示不同的洗衣模式，同时修改步进电机的工作逻辑以适应当前工作模式。

更换材质按钮按下，单片机识别后蜂鸣器发声，修改衣物材质，更改LCD显示屏的衣物材质显示，同时修改步进电机的工作逻辑以适应当前工作模式。

定时预约按钮按下，单片机识别后蜂鸣器发声，自动预约在30分钟后开始或停止洗衣，并在LCD显示屏上显示相应的预约内容。

### **2.4 总体电路**

总体电路由STM32F103ZET6单片机、5x5彩灯矩阵、红外接收模块、TFT-LCD显示屏、ADC重量模拟、ULN2003步进电机驱动、RTC时钟模块组成。系统框图如下

<img src="Doc\原理图\原理框图.png" alt="原理框图" style="zoom:25%;" />

### **2.5 局部电路**

#### 2.5.1 STM32F103ZET6

51 是嵌入式学习中一款入门级的精典 MCU，因其结构简单，易于教学，且可以通过串口编程而不需要额外的仿真器，所以在教学时被大量采用，至今很多大学在嵌入式教学 中用的还是 51。51 诞生于 70 年代， 属于传统的 8 位单片机，如今，久经岁月的洗礼，既 有其辉煌又有其不足。现在的市场产品竞争越来越激烈，对成本极其敏感， 相应地对 MCU 的性能要求也更苛刻：更多功能，更低功耗，易用界面和多任务。面对这些要求，51 现有的 资源就显得得抓襟见肘。 所以无论是高校教学还是市场需求，都急需一款新的 MCU 来 为这个领域注入新的活力。

基于这样的市场需求， ARM 公司推出了其全新的基于 ARMv7 架构的 32 位 Cortex-M3 微控制器内核。 紧随其后，ST（意法半导体）公司就推出了基于 Cortex-M3 内核的 MCU—STM32。STM32 凭借其产品线的多样化、 极高的性价比、简单易用的库开发方式，迅速在众多Cortex-M3 MCU 中脱颖而出，成为最闪亮的一颗新星。 STM32 一上市就迅速占领了中低端 MCU 市场，受到了市场和工程师的无比青睐，颇有星火燎原之势。

STM32作为一个微控制器，自带了各种常用通信接口，比如USART、I2C、SPI等，可接非常多的传感器，可以控制很多的设备。 现实生活中，我们接触到的很多电器产品都有STM32的身影，比如智能手环，微型四轴飞行器，平衡车、移动POST机，智能电饭锅， 3D打印机等等。

本设计选用的STM32F103ZET6 是一款基于 ARM Cortex-M3 内核的 32 位微控制器。它属于 STM32 系列中的 F1 系列，主频高达 72 MHz，内置 512 KB Flash 和 64 KB SRAM，支持多种通信接口如 USART、SPI 和 I2C，并具备 12 位 ADC、PWM 输出及低功耗模式，非常适合消费电子、工业自动化和智能家居等嵌入式应用。其丰富的外设和强大功能使其成为开发者的热门选择。

<img src="C:\Users\Admin\Desktop\电子工程师课设\laundry-machine\Doc\原理图\CPU.png" alt="CPU" style="zoom:75%;" />

#### 2.5.2 TFT-LCD彩屏模块

TFT LCD是一种利用串行数据传输协议与微控制器或其他设备进行通信的显示技术。这种方式通常通过TTL串口（如UART）实现，允许用户通过较少的引脚连接来控制显示器，简化了电路设计。该系统的工作原理是将图像数据和控制命令以串行格式发送到TFT LCD模块，模块内部的控制器解析这些数据，并相应地在液晶屏上绘制图像或文本。与并行通信相比，串口通信的连接更为简单，适合于空间有限的应用场景。

此外，基于串口的TFT LCD支持多种分辨率和色彩深度，能够显示丰富的图形和动画。开发者可以使用标准的AT指令集或自定义命令来实现复杂的图形界面，且许多现成的库和示例代码可供参考，加速开发进程。这种通信方式广泛应用于便携式设备、嵌入式系统和物联网产品中，因其灵活性和易用性受到了开发者的青睐。



<img src="Doc\原理图\TFTLCD.png" alt="TFTLCD" style="zoom:50%;" />

#### 2.5.3 5x5RGB彩灯点阵模块

彩灯模块是开发板上的 5x5 RGB 彩灯阵列，内置 WS2812B 驱动芯片，WS2812B是一种广泛应用于LED照明和装饰的智能RGB LED驱动芯片，每个WS2812B LED模块都集成了一个高性能的RGB LED和一个控制电路，通过单总线串行通信方式，能够实现全彩色的显示效果。该芯片采用一线串行数据传输方式，通过单个数据线就可以控制多个LED，简化了电路设计和布线。这种设计使得用户只需通过微控制器发送特定的数字信号即可实现对每个LED的独立调光和颜色调节，支持256级亮度和1670万种颜色的组合，能够创建丰富多彩的灯光效果。

此外，WS2812B具有较快的刷新速率和极低的延迟，非常适合用于动态灯光效果和动画。其工作电压为5V，内置的电流限制和热保护功能提高了系统的稳定性和安全性。这种芯片被广泛应用于LED灯带、舞台灯光、汽车灯饰以及各种创意照明项目中，因其易于控制、灵活性强而受到开发者和爱好者的青睐。

<img src="\Doc\原理图\RGB5x5.png" alt="RGB5x5" style="zoom:50%;" />

#### 2.5.4 ULN2003AN步进电机驱动模块

ULN2003步进电机驱动模块是一款常见且实用的电路板，专门用于控制步进电机，尤其是与 28BYJ-48 等小型步进电机搭配使用。该模块集成了 ULN2003驱动芯片，提供多达 7 个输出通道，能够驱动高达 500 mA 的电流，使其适合于各种负载条件。

单片机向 ULN2003 模块的输入引脚以特定顺序发送高低电平脉冲，ULN2003 模块接收到信号后，会根据输入电平的变化，驱动相应的输出引脚，向步进电机的线圈供电，从而使电机按照预定的方向和步幅旋转，在运行过程中，可以根据需要调整输入信号的频率，以控制电机的转速。

此外，ULN2003AN 结构紧凑、稳定性高，广泛应用于机器人、自动化设备及其他需要精确运动控制的项目中，为开发者提供了一个高效、可靠的解决方案来实现各种创意和功能。

<img src="Doc\原理图\步进电机.png" alt="步进电机" style="zoom:50%;" />

#### 2.5.5 蜂鸣器模块

<img src="C:\Users\Admin\Desktop\电子工程师课设\laundry-machine\Doc\原理图\BEEP.png" alt="BEEP" style="zoom:50%;" />

电路选择无源蜂鸣器，单片机通过改变连接蜂鸣器的引脚电平，生成2~5 kHz的方波以驱动蜂鸣器发声。蜂鸣器的正极通过保护电阻连接到5 V电源。驱动电路使用ULN2003A达林顿晶体管阵列芯片，输入端连接到单片机的P2.5引脚，输出端连接到蜂鸣器的负极。单片机根据弹奏输入或歌曲信息，通过定时器中断控制引脚输出特定频率信号脉冲，经过驱动芯片放大后驱动蜂鸣器发出声音。

#### 2.5.6 RTC时钟模块

RTC（实时时钟）时钟模块是一种用于提供精确时间和日期的电子组件，广泛应用于各种嵌入式系统和电子项目中。RTC模块通常包括一个低功耗的时钟芯片、一个电池供电的备用源，以及用于设置和读取时间的接口（如I2C或SPI）。

该模块能够在断电的情况下继续保持时间，通常通过内置的锂电池或超级电容供电，以确保在主设备断电时依然能够准确计时。RTC时钟模块的主要功能是提供年、月、日、时、分、秒等时间信息，并且具有较高的精度，能够满足大多数应用需求。使用时，开发者可以通过与微控制器通信来读取当前时间或设置新的时间，方便实现定时任务、数据记录和时间戳功能。

此外，许多RTC模块还集成了闹钟功能、温度传感器或EEPROM存储器，使其更具灵活性。常见的RTC模块，如DS1307和DS3231，不仅操作简单，而且价格低廉，因而被广泛应用于物联网设备、智能家居、电子钟表、自动化控制系统等领域，为各种应用提供了可靠的时间基准。

<img src="Doc\原理图\RTC.png" alt="RTC" style="zoom:60%;" />

#### 2.5.7 ADC模块

ADC（模数转换器）模块是一种将模拟信号转换为数字信号的电子组件，广泛应用于各种嵌入式系统和数据采集设备中。其主要功能是接收连续变化的模拟电压信号，并通过一定的采样率和分辨率，将其转换为对应的数字值，以便微控制器或计算机进行处理和分析。

ADC模块的工作原理通常包括采样、量化和编码三个步骤，能够实现对模拟信号的高精度捕捉。常见的ADC模块有多种位数，如8位、10位、12位甚至16位，分辨率越高，转换结果的精度也越高。在实际应用中，ADC模块可用于监测传感器输出（如温度、光照、压力等），音频信号处理，以及与物联网设备的实时数据传输等场景。许多现代微控制器都内置ADC功能，但外部ADC模块仍然被广泛使用，以满足更高的采样率或更好的性能需求。

此外，ADC模块通常配有SPI、I2C等通信接口，使其易于与其他电子组件集成，方便工程师在各种项目中实现精确的数据采集和处理。由于其在自动化、监测和控制等领域的重要性，ADC模块成为电子设计中不可或缺的部分。

<img src="C:\Users\Admin\Desktop\电子工程师课设\laundry-machine\Doc\原理图\ADC.png" alt="ADC" style="zoom:40%;" />



#### 2.5.8 红外接收模块

红外接收模块是一种用于接收红外信号的电子组件，广泛应用于遥控器、智能家居和各种无线通信系统中。该模块通常由一个红外接收二极管和相关的信号处理电路组成，能够检测特定波长的红外光信号（一般为38kHz频率的调制信号），并将其转换为电信号输出。当遥控器发射红外信号时，红外接收模块接收到的信号经过放大和解调后，可以输出对应的数字脉冲信号。其工作原理相对简单，通常只需连接电源和信号引脚即可使用，适合与微控制器或开发板（如Arduino）配合使用。

此外，红外接收模块具有较强的抗干扰能力和较远的接收距离，通常在几米到十几米之间，具体取决于环境和发射器的功率。这种模块不仅可以用于电视、空调等家电的遥控，还能在机器人、安防系统及自动化设备中实现无线控制功能，因其成本低、易于集成而受到广大电子爱好者和工程师的青睐。

<img src="Doc\原理图\IRED.png" alt="IRED" style="zoom:33%;" />

## 3、系统程序设计

### 3.1 程序开发环境

本设计采用Keil编译器进行程序开发。Keil µVision是ARM公司推出的一款集成开发环境（IDE），专为基于ARM内核的微控制器的开发与调试而设计。该环境提供了全面的工具集，包括编辑器、编译器、调试器和仿真器，旨在帮助开发者高效地进行嵌入式系统的开发工作。

通过Keil编译器，开发者能够轻松编译C源代码和汇编语言，连接和重定位目标文件及库文件，同时生成HEX文件以供下载。这个编译器的功能强大，使得开发过程更为顺畅且高效。Keil编译器的主要组成部分包括：

1. **编辑器**：用于编写和修改源代码，支持语法高亮和代码补全功能。
2. **编译器**：将源代码转换为机器码，确保代码的正确性和效率。
3. **调试器**：提供实时调试功能，能够单步执行、设置断点和监视变量，方便开发者排查问题。
4. **仿真器**：模拟微控制器的运行环境，帮助开发者在实际硬件未到位时进行测试。
5. **库管理工具**：便于管理各种标准库和自定义库，提高代码复用率。

### 3.2 程序总体设计（缺程序框图）

需要完成以下任务：

检测键码，根据检测到的键码不同实现不同的功能，若为模式更换按键，则更改洗衣模式；若为材质更换按键，则更改内部设定的衣物材质；若为工作控制按键，则实现电机工作的开始与停止；若为预约定时按键，则启动预约定时功能，用户在按键按下后能在固定时间后实现电机的启动与关闭。

### 3.3 系统功能介绍

#### 3.3.1 不同模式下洗衣功能的设计

单片机内置多种洗衣模式，使用户能够根据不同的洗涤需求进行选择。这一过程依赖于单片机的多种功能模块和原理。

用户可以通过按键或红外遥控器输入信号。按键输入通常使用电阻分压原理，单片机通过数字输入端口读取按键状态，并将其转换为相应的数字信号。当用户按下某个按键时，单片机会识别该信号并确定所选的洗衣模式。另一方面，红外遥控功能则依赖于一个红外接收模块，它捕获来自遥控器发出的红外信号。单片机内部包含解码算法，能够解析不同的遥控指令，从而改变洗衣模式。

一旦用户选择了特定的洗衣模式，单片机会调用相应的预设程序，这些程序存储在单片机的闪存中。每种洗衣模式对应着不同的洗涤参数，如水温、洗涤时间、旋转速度等。单片机的控制算法会实时调整这些参数，以确保最佳的洗涤效果和能效。

此外，单片机还具备实时监控和反馈功能。它可以通过传感器持续采集洗衣桶内负载信息，确保洗涤过程与所选模式一致。这种智能化设计不仅提升了用户体验，还提高了洗衣机的操作效率，确保各种衣物都能得到适当的处理。

#### 3.3.2 不同物料下洗衣功能的设计

单片机通过内置的程序和存储器，可以支持多种衣物材质的设定，以便用户根据不同类型的衣物进行专业化处理。这一过程涉及到多个技术原理。

用户可以通过按键或红外遥控器输入信号，单片机的输入接口会将这些信号转换为数字格式。按键输入通常依赖于电阻分压原理，单片机借此读取按键状态。而红外遥控则通过接收模块获取遥控器发出的红外信号，单片机内置的解码程序能够识别不同的遥控指令，从而实现对衣物材质的选择。

一旦用户选择了特定的衣物材质，单片机会根据预设的程序逻辑调用相应的洗涤参数，例如水温、洗涤时间和脱水速度等。这些参数的设定通常存储在单片机的闪存中，以便在后续操作中快速访问。单片机内部的控制算法会实时处理这些参数，确保洗衣过程符合用户选择的材质要求。

此外，单片机的实时监控能力使其能够在洗衣过程中持续采集和分析洗衣桶内负载信息，以确保洗涤效果与用户设定的材质匹配。这种灵活性和智能化设计不仅提高了洗衣机的使用便利性，还确保了对不同衣物的专业化处理，从而延长衣物的使用寿命。

#### 3.3.3 衣物洗涤信息的显示功能设计

通过TFT LCD显示屏的实时更新，单片机能够动态地展示当前的工作状态和相关信息。这一过程涉及到单片机的多个核心原理和组件。

首先，单片机通过其内置的图形处理模块与TFT LCD屏幕进行通信。该通信基于串口实现，其允许单片机与显示屏之间高效地传输数据。单片机周期性地向显示屏发送指令和图像数据，以更新显示内容。

在用户操作过程中，单片机会接收来自按键或触摸屏的输入信号。这些输入信号经过ADC（模数转换器）处理，转换为数字格式，使单片机能够识别用户的选择。一旦确定了用户的输入，单片机就会根据预设的逻辑和条件，调用相应的显示程序。

为了实现实时更新，单片机内部的控制算法会不断监测系统状态，如洗衣进程、时间倒计时、温度等参数，并将这些信息实时更新到TFT LCD屏幕上。这样，用户可以直观地了解到设备的当前状态和操作进度。这种智能化设计不仅提升了用户体验，使得洗衣机在运行过程中更加高效和便捷。

#### 3.3.4 定时和预约洗衣功能的设计

单片机内置的实时时钟（RTC）模块是一个重要的功能组件，用于跟踪和记录当前的时间。RTC模块通常包含一个低功耗的计时器，能够在断电状态下继续运行，从而保持准确的时间信息。这一特性使得单片机可以支持定时任务和时间相关的操作。

用户通过RTC模块可以方便地设定当前时间和日期。当设定完成后，RTC会持续更新其内部的时间寄存器，以便提供精确的时间信息。在实际应用中，单片机可以通过读取RTC的时间数据来判断何时需要执行特定的任务。

为了实现洗衣的定时预约功能，单片机利用RTC内置的定时中断机制。当用户设定一个预约时间后，RTC会在到达该时间点时触发一个中断信号。单片机在响应这个中断时，可以修改洗衣状态标志位，从而启动或停止洗衣程序。这种机制使得用户能够灵活地安排洗衣时间，提高了设备的智能化水平。

通过这种方式，单片机不仅能执行基本的控制任务，还能实现复杂的定时逻辑。RTC模块的精确性和可靠性直接影响到定时功能的效果，因此在设计时需要合理配置时钟源和中断优先级，以确保系统的稳定性和实时性。

#### 3.3.5 模拟衣物重量功能的设计

单片机内置了模数转换器（ADC）模块，使其能够将模拟信号转换为数字信号。ADC的工作原理是通过对输入的模拟电压进行采样，并将其转换为对应的数字值。这一过程通常涉及多个步骤，包括采样、量化和编码。

在本设计中，我们利用ADC与一个电位器相连接。电位器的电阻值可调，通过旋转电位器，改变其输出电压，从而影响ADC所读取的电压值。具体来说，当电位器的阻值变化时，输出的电压也随之变化，这个电压作为单片机ADC的输入信号。通过对这个信号进行数字化处理，单片机可以根据设定的算法，将获取的数字值转换成相应的衣物重量的模拟数据。

这样的设计不仅实现了对衣物重量的测量，还展示了单片机在传感器信号处理中的应用潜力。ADC模块的分辨率和采样速率直接影响到测量的精度，因此在实际应用中，选择合适的ADC参数至关重要。通过合理的电路设计和软件算法，可以进一步提升系统的整体性能和准确性。

## 4、系统测试与实现

### 4.1 软件开发环境

#### 4.1.1 Keil编译器

Keil 编译器是本设计所选用的编程工具，用于进行简单仿真。Keil µVision 是 ARM 公司推出的集成开发环境（IDE），专门用于开发和调试基于 ARM 内核的微控制器。该环境提供了全面的工具集，包括编辑器、编译器、调试器和仿真器，帮助开发者高效完成嵌入式系统开发。 

Keil IDE 拥有直观的用户界面，使用起来非常便捷，即使是初学者也能快速上手。此外，它支持多种 ARM 内核，并能够与各种外部工具无缝集成，为开发者提供了灵活性和便利性。以下是工程文件的介绍：

**Doc：**工程说明

**Libraries：**

CMSIS-内置CM3内核相关的库文件

STM32F10x_StdPeriph_Drivers-STM32外设库文件

**HARDWARE：**

各类外设相关的代码，包括各个模块的驱动程序，定时器、外部中断的配置文件

**User：**

main.c 主函数存放

stm32f10x_conf.h：用来配置库的头文件

stm32f10x_it.c：中断相关的函数都在这个文件编写，暂时为空

#### 4.1.2 Protues仿真

### 4.2 系统仿真与实现

#### 4.2.1 编写源程序代码

打开 Keil 5，创建工程并编写源代码。代码编写完成后，点击编译。如果有错误则进行修正；如果没有错误，则生成 .hex 文件。该 .hex 文件格式可以烧录到单片机中并被其执行。

#### 4.2.2 Protues仿真

### 4.3 实物测试

#### 4.3.1 洗衣模式设定

通过按下KEY_UP按钮或接收红外信号“0x629D”，用户可以实现洗衣模式的切换。这一功能依靠单片机的多种原理和组件协同工作。

首先，当用户按下KEY_UP按钮时，单片机的GPIO（通用输入输出）端口会监测到这个按键的状态变化。按键的压制会导致电路中的电平变化，单片机通过内置的中断机制能够立即响应这一变化，从而触发相应的程序逻辑。同时，如果使用红外遥控器发送“0x629D”信号，单片机内部的红外接收模块将捕捉到该信号，并通过解码算法识别为洗衣模式切换指令。

一旦确认了用户的输入，单片机会根据预设的逻辑选择相应的洗衣模式。此时，单片机会调取与每种洗衣模式对应的参数设置，为了向用户提供直观反馈，单片机会控制TFT LCD显示屏和RGB彩灯矩阵的状态。

在显示方面，单片机通过图形处理模块更新TFT LCD屏幕，实时显示当前的工作状态和所选的洗衣模式。同时，为了提供额外的视觉提示，单片机还会控制RGB彩灯矩阵的颜色变化：红灯代表模式1，绿灯代表模式2，蓝灯代表模式3，青灯代表模式4。每种颜色的LED灯由单片机的PWM（脉宽调制）控制，允许精确调节灯光的亮度和色彩，这样用户可以清楚地看到当前的工作状态。

![模式切换后](Doc\实物图\模式切换后.jpg)

#### 4.3.2 衣物材质设定

通过按下KEY_0按钮或接收红外信号“0xC23D”，用户可以实现衣物材质的切换。这一过程依赖于单片机的多种功能和原理。

首先，当用户按下KEY_0按钮时，单片机的GPIO（通用输入输出）端口会检测到按钮的状态变化。此时，单片机内部的中断系统会迅速捕捉到这一变化，并触发相应的程序逻辑，以进行衣物材质的切换。同样，如果用户使用红外遥控器发送特定的信号“0xC23D”，单片机内置的红外接收模块将接收到这个信号，并通过解码算法确认这是一个材质切换指令。

在确认用户输入后，单片机会根据设定的逻辑更新当前衣物材质。系统中定义了三种材质：丝质（0）、棉质（1）和其他（2）。单片机通过查找表或条件判断来确定当前选择的材质，并将其存储在内部变量中，以便后续处理。

为了向用户提供直观的反馈，单片机会控制TFT LCD显示屏实时更新当前所选的衣物材质。单片机通过串口与TFT LCD进行通信，发送显示数据和命令，使屏幕上能够反映出用户选择的材质类型。比如，屏幕上会以文本方式显示“0”、“1”或“2”。

此外，单片机还可以利用定时器和中断机制，确保LCD的更新频率适当，从而使显示内容流畅且响应及时。通过这种方式，用户不仅能够方便地切换衣物材质，还能实时查看当前选择，这增强了设备的可操作性和用户体验。

![衣物材质切换后](Doc\实物图\衣物材质切换后.jpg)

#### 4.3.3 启停功能、信息显示功能

![步进电机工作图](Doc\实物图\步进电机工作图.jpg)

当用户按下KEY_2按钮时，单片机的GPIO（通用输入输出）端口会检测到这一状态变化。单片机内部的中断系统将立即响应该变化，并执行相应的程序逻辑以控制电机的启动或停止。此外，如果用户使用红外遥控器发送信号“0x22DD”，单片机内置的红外接收模块能够捕捉到该信号，并进行解码，以确认这是一个电机控制指令。

在电机启停的过程中，单片机利用其定时器功能来依次控制步进电机的步进序列。步进电机的驱动原理是通过依次激活其多个线圈，使电机转子逐步旋转。单片机会按照设定的步进序列，实时切换四个引脚的高低电平，从而产生对电机线圈的激励信号。这些信号经过ULN2003驱动电路，进一步增强电流以满足步进电机的驱动需求。

具体而言，ULN2003是一个七路高电平至低电平的驱动器，可以有效地将单片机输出的逻辑信号转换为可驱动步进电机所需的较高电流。单片机会通过定时器精确控制每个引脚的激励时序，比如设置合适的时间间隔，以确保电机按预定速度平稳运行。

为了向用户提供实时反馈，单片机还会通过TFT LCD显示屏更新当前步进电机的工作状态。例如，当电机开启时，LCD上将显示“Step motor: Start”，而在停止时则显示“Step motor: Stop”。显示的内容由单片机通过串口与LCD进行通信，及时更新电机的状态信息。

通过这种方式，用户不仅可以方便地控制步进电机的启停，还能清晰地了解电机的当前状态，从而提升了设备的操作体验和可靠性。

#### 4.3.4 定时预约功能测试

![定时预约](Doc\实物图\定时预约.jpg)

按下KEY_1按钮或输入红外信号“0xA857”可以实现洗衣机的定时预约功能。这一过程依赖于单片机的控制原理。

当用户按下KEY_1按钮时，单片机通过其GPIO（通用输入输出）引脚检测到按键输入。随后，单片机内部的定时器模块被激活，开始计时。在电机处于停止状态时，单片机会更新LCD显示屏，显示信息“RTC_ALR_SET START”，指示用户定时预约已启动。此时，单片机会在30秒后发出控制信号，启动电机，开始洗衣程序。

如果在电机正在运行的状态下再次启动该预约功能，单片机同样会利用定时器进行计时，并在30秒后自动关闭电机。在这种情况下，LCD显示屏会更新为“RTC_ALR_SET STOP”，提醒用户电机即将停止。

整个过程中，单片机不仅负责用户输入的监测和响应，还通过其内置的实时钟（RTC）和定时器，确保时间的精准控制。此外，单片机的中断处理机制也保证了系统能够及时响应用户的操作，从而提升了洗衣机的智能化水平和用户体验。

#### 4.3.5 衣物重量模拟功能测试

通过单片机的A/D（模数转换）模块，可以实时监测洗衣机内衣物的重量。当用户将衣物放入洗衣机时，传感器将该重量信号转换为模拟电压信号，然后通过A/D模块将其转换为数字信号供单片机处理。

在这一过程中，单片机不断读取来自A/D模块的数字输出，并对其进行分析。单片机内置的算法会将当前读取的重量与预设的最大承载值进行比较。如果检测到衣物重量超过设定的阈值，单片机会触发超重提示，通过LCD显示屏或指示灯向用户发出警告。这一机制不仅确保了设备的安全运行，还帮助用户避免可能因过载而导致的洗衣机损坏。另外，单片机的实时处理能力和高效的控制逻辑确保了重量监测的准确性和及时性，使得用户能够获得良好的操作体验。

![ADC重量模拟](Doc\实物图\ADC重量模拟.jpg)

#### 4.3.6 系统总工作图

![系统总工作图](Doc\实物图\系统总工作图.jpg)

## 5、结论

本次设计的全自动洗衣机控制系统充分展示了单片机在测控领域的应用。该系统能够根据所设置的洗涤和漂洗方式。通过引入模糊称重技术，实现了真正的全自动控制，用户只需按一个按钮即可自动判断衣物的多少，调整水位并完成洗涤过程。同时，系统还为用户提供个性化选择，通过按键和显示界面，用户可以指定所需的水位和特定的洗涤程序，满足个性化的洗涤需求，从而圆满达成任务目标。

在此次设计过程中，我获取到一些国内外市场洗衣机的信息，拓宽了视野。同时，对洗衣机电脑板各部分电路设计及其性能参数有了更深入的认识，对软件设计和结构的把握也更加到位，加深了对软硬件设计的理解。在软硬件调试过程中，总结了经验，发现了自身存在的不足，并及时调整，以避免在未来设计中犯类似错误。

## 引用：

[1]段倩倩.物联网滚筒洗衣机控制系统的设计与实现[D].济南大学,2021.DOI:10.27166/d.cnki.gsdcc.2021.000388.

[2]童飞.直驱式滚筒洗衣机驱动控制系统设计及实现[D].南京理工大学,2012.

[3]张海波.全自动洗衣机控制器的设计[D].南京理工大学,2012.

[4]方玉鑫.基于单片机的温湿度控制系统的研究与应用[D].哈尔滨工程大学,2012.

[5]魏春杰.嵌入式实时操作系统UCOS-Ⅱ应用技术研究[D].大连海事大学,2004.

[6]邵贝贝.单片机技术的发展与单片机应用的广泛选择[J].电子技术应用,1999,(03):3-5.

[7]刘心红,郭福田,孙振兴,等.Proteus仿真技术在单片机教学中的应用[J].实验技术与管理,2007,(03):96-98+102.DOI:10.16791/j.cnki.sjg.2007.03.029.

[8]王桂兰.基于Protues和Keil软件的51单片机数字通信设计与仿真[J].产业与科技论坛,2024,23(08):53-55.

[9]王海燕,杨艳华.Proteus和Keil软件在单片机实验教学中的应用[J].实验室研究与探索,2012,31(05):88-91.

## **Based on:**

普中

## 附录-主要代码：

```c
#include "stm32f10x.h"
#include "timer.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "rtc.h" 
#include "adc.h"
#include "key.h"
#include "beep.h"
#include "hwjs.h"
#include "stepper.h"
#include "touch_key.h"
#include "pwm.h"
#include "ws2812.h"

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int step_cir = 0;	
u8 step_run = 0;
u8 step_reverse = 0;
u32 step_speed = 1;

u8 status = 0;

u8 mode = 0;
u8 texture = 0;

u8 set_min = 0;
u8 set_hour = 0;

u8 rtc_alt = 0;
u8 keypad = 255;
	
int main()
{
	static u8 key = 1;
	static u8 touch_key = 0;

	u16 main_time = 0;
	u16 adc_value = 0;
	float adc_voltage = 0;
	u8 str_tmp[24],float_tmp[6];
	u32 color[]={RGB_COLOR_RED,RGB_COLOR_GREEN,
								RGB_COLOR_BLUE,RGB_COLOR_WHITE,RGB_COLOR_YELLOW};
	
	int pwm_value=0;					
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	
	LED_Init();
	RTC_Init();
	RTC_Set(2024,10,8,8,50,00);
	
	ADCx_Init();
	KEY_Init();
	Touch_Key_Init(6);
	Hwjs_Init();
	BEEP_Init();
	RGB_LED_Init();
//	My_EXTI_Init();
	
	Stepper_Config();
	TIM4_Init();
	
	TIM2_CH3_PWM_Init(100,72-1); //频率是2Kh
	TIM_SetCompare3(TIM2,0);
	
	RTC_ClearITPendingBit(RTC_IT_ALR);
	
	LCD_Init();
	POINT_COLOR=RED;
	
	LCD_ShowString(70,10,200,16,16,"HFUT GXJ 2021218017");
	LCD_ShowString(70,30,200,16,16,"HFUT LLH 2021218032");
	LCD_ShowString(30,130,320,16,16,"HWJS:          ");
//	LCD_ShowString(30,170,320,16,16,"RTC Alrt:    -  -     :  :  ");
	LCD_ShowString(30,220,320,16,16,"Machine Status:     ");
	LCD_ShowString(30,240,320,16,16,"RTC Time:    -  -     :  :  ");
	LCD_ShowString(30,260,320,16,16,"AD was detected:      ");
	LCD_ShowString(30,280,320,16,16,"Detective voltage:     V");
	LCD_ShowString(30,320,320,16,16,"Key pressed: ");	
	LCD_ShowString(30,340,320,16,16,"The motor speed is:    %");	
	LCD_ShowString(30,380,320,16,16,"The mode is:     ");	
	
	
	Chinese_Show_one(100,50,0,24,0,0);		
	Chinese_Show_one(124,50,1,24,0,0);	 	
	Chinese_Show_one(148,50,2,24,0,0);		
	Chinese_Show_one(172,50,3,24,0,0);
	Chinese_Show_one(196,50,4,24,0,0);
	
	while(1)
	{
		if(main_time % 5000){
//			LED1=!LED1;
		}
		
		/*********  RTC时间显示  *********/
		if(main_time % 1000){
			RTC_Get();
			LCD_ShowxNum(102,240,calendar.w_year,4,16,0);
			LCD_ShowxNum(142,240,calendar.w_month,2,16,0);
			LCD_ShowxNum(166,240,calendar.w_date,2,16,0);
			LCD_ShowxNum(190,240,calendar.hour,2,16,0);
			LCD_ShowxNum(214,240,calendar.min,2,16,0);
			LCD_ShowxNum(236,240,calendar.sec,2,16,0);
		}
		
		/*********  ADC状态检测  *********/
		if(main_time % 1000){
			adc_value = Get_ADC_Value(ADC_Channel_1,20);
			LCD_ShowxNum(174,260,adc_value,4,16,0);
			adc_voltage = (float)adc_value*(3.3/4096);
			sprintf((char*)float_tmp,"%.2f",adc_voltage);
			LCD_ShowString(175,280,32,16,16,float_tmp);	
			if(adc_voltage < 2.0){
				LCD_ShowString(30,400,320,16,16,"Adc is too low.");	
			}else{
				LCD_ShowString(30,400,320,16,16,"Adc works fine.  ");
			}
		}
		
		/*********  按键检测  *********/
//		if(main_time % 25){
//			if(keypad==0)
//				LCD_ShowString(30,320,320,16,16,"Key pressed: Change Mode Set           ");	
//			else if (keypad==1)
//				LCD_ShowString(30,320,320,16,16,"Key pressed: Start Work             ");
//			else if (keypad==2)
//				LCD_ShowString(30,320,320,16,16,"Key pressed: Appointment Time Set        ");
//			else if (keypad==3)
//				LCD_ShowString(30,320,320,16,16,"Key pressed: Clothes Texture Set          ");
//		}
		
		if(main_time % 25){
			key = KEY_Scan(0);
			switch(key){
				case KEY_UP_PRESS:	//调模式
					mode = mode+1;
					LED2 = 0; 
					LCD_ShowString(30,320,320,16,16,"Key pressed: Change Mode Set           ");		
					break;
				
				case KEY1_PRESS: 		//定时预约
					
					set_hour = calendar.hour;
					set_min = calendar.min + 1;
					if (set_min>59){
						set_min = 0;
						set_hour = set_hour + 1;
					}
					
//					RTC_Alarm_Set(calendar.w_year,calendar.w_month,calendar.w_date,
//												set_hour,set_min,0);
					RTC_SetAlarm(5+RTC_GetCounter());		//预约5秒
					
					LED2 = 1;
					LCD_ShowString(30,320,320,16,16,"Key pressed: Appointment Time Set        ");
					break;
				case KEY2_PRESS:	//启动停止
					
					BEEP=1;
					delay_ms(100);
					BEEP=0;
				
					status = !status;
					step_run =!step_run;
					LCD_ShowString(30,320,320,16,16,"Key pressed: Start Work             ");
					break;
				case KEY0_PRESS:	//衣物材质设定
					
					BEEP=1;
					delay_ms(100);
					BEEP=0;

					texture++;
					LCD_ShowString(30,320,320,16,16,"Key pressed: Clothes Texture Set          ");
					break;
			}
		}
		
			
		
		/*********  定时显示  *********/
		
//		if(main_time % 1000){
//			RTC_Get();
//			LCD_ShowxNum(102,170,calendar.w_year,4,16,0);
//			LCD_ShowxNum(142,170,calendar.w_month,2,16,0);
//			LCD_ShowxNum(166,170,calendar.w_date,2,16,0);
//			LCD_ShowxNum(190,170,set_hour,2,16,0);
//			LCD_ShowxNum(214,170,set_min,2,16,0);
//			LCD_ShowxNum(236,170,0,2,16,0);
//		}
		
		/*********  触摸按键  *********/
		if(main_time % 35){
			touch_key = Touch_Key_Scan(0);
			if(touch_key == 1){
				LCD_ShowString(30,320,320,16,16,"Key pressed: touch");
				LED1=!LED1;
			}
		}
		
		/*********  红外遥控  *********/
		if(main_time % 100){
			if(hw_jsbz==1)	//如果红外接收到
			{
				hw_jsbz=0;	   //清零
				printf("红外接收码 %0.8X\r\n",hw_jsm);	//打印
				sprintf((char*)str_tmp,"Hwjs %0.8X",hw_jsm);
				LCD_ShowString(30,130,320,16,16,str_tmp);	
				
				if(hw_jsm == 0x00FF629D){
					BEEP=1;
					delay_ms(10);
					BEEP=0;
					mode = mode+1;
				}
				else if(hw_jsm == 0x00FFA857){
					BEEP=1;
					delay_ms(10);
					BEEP=0;
					RTC_SetAlarm(5+RTC_GetCounter());
				}
				else if(hw_jsm == 0x00FF22DD){
					BEEP=1;
					delay_ms(10);
					BEEP=0;
//					status = !status;
					step_run =!step_run;
				}
				else if(hw_jsm == 0x00FFC23D){
					BEEP=1;
					delay_ms(10);
					BEEP=0;
					texture++;
				}
				else if(hw_jsm == 0x00FF02FD){
					BEEP=1;
					delay_ms(10);
					BEEP=0;
					step_reverse = !step_reverse;
					LCD_ShowString(30,70,320,16,16,"Step motor: REVERSED ");
				}
				else{
					LCD_ShowString(200,130,320,16,16,"not!");	
				}
				hw_jsm=0;					//接收码清零
			}				
		}
		
		/*********  状态更新  *********/
		if(main_time % 100){
			if(mode % 4 == 0){
				mode = 0;
			}else if(mode == 255){
				mode = 3;
			}
			LCD_ShowxNum(174,380,mode,4,16,0);
			
			
			if(texture % 3 == 0){
				texture = 0;
			}
			
			if(rtc_alt ==0){
				LCD_ShowString(30,150,320,16,16,"RTC_ALR SET START   ");
			}else if (rtc_alt ==1)
				LCD_ShowString(30,150,320,16,16,"RTC_ALR SET STOP   ");
			
			switch(mode){
				case 0:
					pwm_value=25-5*texture;
					step_speed = 230400-5000*texture;
					break;
				case 1:
					pwm_value=50-5*texture;
					step_speed = 115200-5000*texture;
					break;
				case 2:
					pwm_value=75-5*texture;
					step_speed = 50000-5000*texture;
					break;
				case 3:
					pwm_value=100-5*texture;
					step_speed = 10000-5000*texture;
					break;
			}
			
			switch(texture){
				case 0:
					LCD_ShowString(30,200,320,16,16,"Clothes texture: 000");
					break;
				case 1:
					LCD_ShowString(30,200,320,16,16,"Clothes texture: 001");
					break;
				case 2:
					LCD_ShowString(30,200,320,16,16,"Clothes texture: 002");
					break;
			}
		}
		
		if(main_time % 100){
//			RGB_ShowCharNum(mode,color[mode]);
			switch(mode){
				case 0:
					RGB_LED_Red();
					break;
				case 1:
					RGB_LED_Green();
					break;
				case 2:
					RGB_LED_Blue();
					break;
				case 3:
					RGB_LED_Fuck();
					break;
			}
		}
		
		/*********  直流电机  *********/
		
		if(main_time % 100){
			if (status==0 && adc_voltage > 2.0){
				LCD_ShowString(30,220,320,16,16,"Machine Status: Stop    ");
				TIM_SetCompare3(TIM2,0);
				LCD_ShowxNum(180,340,pwm_value,3,16,0);
			}else if(status==1 && adc_voltage > 2.0){
				LCD_ShowString(30,220,320,16,16,"Machine Status: Start  ");
				TIM_SetCompare3(TIM2,pwm_value);
				LCD_ShowxNum(180,340,pwm_value,3,16,0);
			}
			
			if(adc_voltage < 2.0){
				TIM_SetCompare3(TIM2,0);
				LCD_ShowString(30,220,320,16,16,"Machine Status: ADC low  ");
				LCD_ShowxNum(180,340,pwm_value,3,16,0);
			}
		}		

		
		/*********  步进电机  *********/
		if(step_run != 0){
			step_cir += 2000;
			step_run = 1;
			LCD_ShowString(30,110,320,16,16,"Step motor:Start ");
			TIM4_EnableInterrupt();
		}
		else if(step_run ==0){
			LCD_ShowString(30,110,320,16,16,"Step motor: Stop ");
			TIM4_DisableInterrupt();
		}
		else{
			LCD_ShowxNum(30,380,step_cir,4,16,0);
		}
		
		delay_ms(1);
		main_time++;
		if(main_time >= 1E5) main_time = 0;
	}
}

```


