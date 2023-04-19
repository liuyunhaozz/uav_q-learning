# Autonomous obstacle avoidance of UAV based on Q-Learning





![ue4_drone](/Users/yunhao/Public/uav_q-learning/assets/ue4_drone.gif)



## Introduction

我们本次课程设计的目标是使用 Q-Learning 算法进行无人机的路径规划，检测并记录无人机到达每个无线路由器正上方时该无线路由器的信号强度值。通过实现与路由器最大数据速率传输的方式并且避开障碍物的方式，进行无人机的智能航线规划。同时利用本课程讲授的C++语言面向对象的基本特点，对课程讲解和上机训练的有关内容实践训练。在代码部分，我们采用了面向对象的程序设计思想。在无人机航线规划框架结构的研究中，定义了无人机类，包含飞行半径、平飞速度、垂直飞行速度、最大最小飞行高度等属性，这是类和对象的体现；在静态全局规划和动态局部规划方法的探讨中，定义了两种环境类障碍物类和路由器类作为算法的仿真环境，实现了继承与多态。

![image-20230419200801420](/Users/yunhao/Public/uav_q-learning/assets/image-20230419200801420.png)

## Tools

本次实验中，我们主要选用的工具有：

1. Visual Studio 2019
   我们主要采用Visual Studio 2019来进行代码的编写，IDE版本为16.8.6. 使用ISO C++ 17 标准，操作系统为 Windows 10 x64, 编译器为msvc
2. Unreal Engine 4
   我们采用UE 4 引擎来对无人机运行环境进行3D建模，UE 4 是Epic公司开发的一款游戏开发引擎。 UE 4 是一套完整的构建游戏、模拟和可视化的集成工具，能够满足艺术家的愿景，同时也具备足够的灵活性，可满足不同规模的开发团队需求。
3. Airsim
   我们采用Airsim API进行UE 4 引擎中无人机的控制，Airsim是一款基于Unreal Engine构建的无人机、汽车等模拟器的开源平台，并且可以跨平台地通过PX4飞行控制器进行仿真控制，在物理和视觉上逼真的模拟环境使得它成为一款很好的平台。不仅模拟了汽车无人机等动力学模型，甚至对天气效果灯光控制也做出了非常好的模拟。
4. Fastor张量库
   我们在代码中导入了一个名为Fastor的C++ 张量库，Fastor是现代C++的基于堆栈的高性能张量（固定多维数组）库，用于在C++ 中操作多维数组。

## 实验过程

### 初始化环境

首先，我们在Unreal Engine中为无人机创建了一个环境，该环境我们将其初始化为一个 7 x 7 的网格，每个网格长 10 m，其次，我们在该环境中，设置了不同的建筑作为障碍物，我们将建筑物的海拔分为三个级别，分别为 60 m， 150 m， 250 m。其中高度为 60 m的障碍物 2 个，高度为 150 m的障碍物 8 个，高度为 250 m的障碍物 2 个。最后，我们在该环境中设置五个路由器，路由器在场景中用白色球体表示，无人机的航线必须经过五个路由器，同时应该避开障碍物，以此实现无人机的最优路径。
其中，建筑物和路由器位置都是随机的。

![image-20230419200814072](/Users/yunhao/Public/uav_q-learning/assets/image-20230419200814072.png)

### 初始化无人机

在本次实验设计中，我们定义了一台无人机，我们通过定义无人机的燃料以反馈无人机的飞行半径。然后我们初始化了无人机的飞行速度与平飞速度均为 3 米/秒，初始化无人机的垂直飞行速度为 3 m/s。同时，我们设置了无人机的三种飞行高度，分别为 50m，125m，200m。最后，我们设置无人机可以执行六种动作，分别为向前行驶，向后行驶，向左行驶，向右行驶, 向上行驶，向下行驶。

![image-20230419200821051](/Users/yunhao/Public/uav_q-learning/assets/image-20230419200821051.png)

### 训练无人机

为了优化无人机的路径，我们使用Q-learning算法。Q-learning算法使用未来奖励来影响给定状态的当前动作，因此，我们将它作为最大化奖励的算法。首先我们以无人机的起飞位置作为 Airsim 坐标系的坐标原点，调用 AirsimAPI 获取每个障碍物和路由器在Airsim坐标系中的坐标原点。然后根据环境的不同在奖励矩阵中设置不同的奖励或惩罚。然后我们设置五个路由器为无人机的飞行目标，为每个目标路由器训练了2000 次，整个程序训练 10000 次。根据Q-learning算法，我们初始化Q-table，将Q值表均赋值为 0 选择一个动作，执行动作测量奖励并在每次测试后结束并更新Q-table。

### 实验结果

训练结束后，我们根据得到的Q-Table，使用Q-learning算法来进行无人机的路径规划。并通过Airsim API 控制无人机在UE 4 引擎中进行效果展示，取得了较好的效果

![image-20230419200834045](/Users/yunhao/Public/uav_q-learning/assets/image-20230419200834045.png)

我们接下来更换改变了障碍物的位置，重新进行训练和验证。结果表明，无人机在不同允许环境下都能准确遍历所有路由器，因此该模型具有较好的鲁棒性

![image-20230419200900691](/Users/yunhao/Public/uav_q-learning/assets/image-20230419200900691.png)

![image-20230419200908285](/Users/yunhao/Public/uav_q-learning/assets/image-20230419200908285.png)



## 参考文献

[1] Practical Reinforcement Learning — 02 Getting started with Q-learning
(https://towardsdatascience.com/practical-reinforcement-learning- 02 - getting-started-
with-q-learning-582f63e4acd9)
[2] 通信常识：波特率，数据传输速率和带宽的相互关系
(https://blog.csdn.net/xchbx/article/details/11537951)
[3] Epic Games Unreal Engine 4 Documentation
(https://docs.unrealengine.com/4.27/en-US/)
[4] Microsoft Airsim Documentation
(https://microsoft.github.io/AirSim/)
[5] Fastor-wiki
(https://github.com/romeric/Fastor/wiki/Getting-Started)
[6] Optimizing-UAV-trajectory-for-maximum-data-rate-via-Q-Learning
(https://github.com/khinthandarkyaw98/Optimizing-UAV-trajectory-for-maximum-
data-rate-via-Q-Learning)
[7] airsim详细教程( 1 ): win10配置airsim仿真环境(2021.8.12更新)
(https://zhuanlan.zhihu.com/p/267321662)
[ 8 ] airsim系列(五) - 控制四旋翼的飞行(core api)
(https://zhuanlan.zhihu.com/p/307956920)
[ 9 ] Q learning - epsilon greedy update
(https://stackoverflow.com/questions/48583396/q-learning-epsilon-greedy-update)
[ 10 ] How to Set Up a Grid for Level and Game Design Metrics
(https://www.youtube.com/watch?v=KSXshiA59OA&ab_channel=TylerMcCombs)
[ 11 ] 6.9 — Sharing global constants across multiple files (using inline variables)
(https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-
files-using-inline-variables/)

