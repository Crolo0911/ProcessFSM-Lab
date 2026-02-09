# ProcessFSM-Lab

一个用于学习 Windows 进程操作与有限状态机（FSM）的轻量级实验框架。

本项目定位为：**状态机 + 远程进程基础流程 的学习骨架**，不针对任何真实程序，仅用于理解架构设计与 Windows API 使用方式。

---

## 项目目标

本仓库的核心目的不是“实现功能”，而是：

* 理解有限状态机在工程中的实际用法
* 学习 Windows 进程枚举 / 模块枚举
* 掌握远程进程 Handle 获取流程
* 体验 ReadProcessMemory / VirtualAllocEx 的基本调用方式
* 建立统一的 Context（世界状态）模型
* 用 FSM 驱动整个执行流程，而不是顺序调用函数

这是一个**结构优先**的学习项目。

---

## 状态机流程

整体执行由 FSM 控制：

MatchPid → ApplyForMem → VerifySome → Work → Exit

含义如下：

* MatchPid：定位目标进程（演示用占位名称）
* ApplyForMem：打开进程句柄
* VerifySome：模块枚举 + 基础读探测
* Work：演示远程读写 / 内存申请
* Exit：统一退出

每个状态函数返回 bool，由 FSM 决定下一步走向。

失败统一进入 Exit。

---

## 架构特点

* 使用 enum class 描述状态
* 所有阶段函数统一返回 bool
* NextState 负责状态推进
* Context 结构体集中保存世界信息
* FSM 只关心状态迁移，不关心具体实现细节

这是一个标准的：

FSM + Context + WorkModule 架构雏形。

---

## 包含内容

* 有限状态机驱动主循环
* 进程枚举示例
* 模块枚举示例
* OpenProcess 演示
* ReadProcessMemory 示例
* VirtualAllocEx 示例

所有目标名、RVA、参数均为演示占位。

不包含任何真实程序信息。

---

## 使用说明

本项目适合用于：

* Windows 内核 / 用户态学习
* 状态机架构练习
* 逆向工程前置训练
* 远程进程流程理解

建议配合调试器逐状态单步运行观察。

---

## 声明

本项目仅用于学习 Windows 编程与状态机设计。

不面向任何真实游戏或商业软件。

请合理、合法使用相关知识。
