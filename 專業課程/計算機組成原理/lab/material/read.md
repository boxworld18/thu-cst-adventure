# **计算机组成原理・文档整理**



## RISC-V Spec

### 9 "Zicsr", Control and Status Register(CSR) Instructions

* 格式

* 立即数 (5 位)，高位零扩展

### 概览

* CSRRW
  * `rd = 0` CSR 不读只写
* CSRR{S/C}
  * `rs1 = x0` CSR 只读不写
* CSRRWI
  * `rd = 0` CSR 不读只写
* CSRR{S/C}I
  * `uimm = 0` CSR 只读不写
* 其余情况照常



##### CSRRS

* rs1 作 bitmask，决定 CSR 需要设置值的位置 (当且仅当对应位置可写)

##### CSRRC

* rs1 作 bitmask，决定 CSR 需要清除值的位置 (当且仅当对应位置可写)



* 对于 CSRRS 和 CSRRC 若 `rs1=x0` 则操作无效
* 但对于其他寄存器保存零值形如： `rf[rs1]=0` 则仍会操作，即使可能出现问题
* 而 CSRRW 则不理会此问题，即使 `rs1=x0` 仍然照常写入 CSR 中
* 对于 I 系列指令亦同



* 对于某些 CSR，如 `instret` 指令退出计数器，可能会被修改而产生副作用
  * CSR 访问指令在执行指令前会先读取 CSR，然后直接写入 CSR 而非增加



#### CSR 访存顺序

* 对于所有在 CSR 指令前执行的指令，沿用旧的 CSR 状态

* 在之后的指令，则采用新的 CSR 状态 



## RISC-V Privileged

### 2.2 CSR Listings

* 已分配的 CSR 地址，计时器，浮点 CSR，用户态 CSR 等



### 2.3 CSR Field Specifications

#### WPRI (Write preserve, read ignore)

* 没有用到的硬连线为零，不支持读



#### WLRL

* 要求写的是合法值
* 没有初始化时不能期待读出合法值



#### WARL (Write any, read legal)

* 可以尝试写入再读出，看看值是否被保留而确定支持的范围
* 实现时实入不受支持的值不会报错，但下一次读操作时会返回任意合法值
* 且该值由上次的值决定



### 3.1.6 mstatus

* 当前操作层级
* S/U 层级下操作受限



* xIE=1 代表在当前的状态下可出现层级 x 的中断
* 然而，高层级 x 的中断永远可以在低层级 y 的状态下发生，无论当前的 xIE 是否为一
* 为了支持巢状中断，每级特权态 x 有两级栈的可干扰字段
  * 其中，xPIE 表示 IE 的优先级高于 trap
  * 而 xPP 则表示之前的特权态
  * 由于 xPP 只能表示 x 或以下层级的特权态，故 MPP 有两位，SPP 只需要一位
  * 当一个 trap 从特权态 y 到 x 时，xPIE 会被设置为 xIE 的值，然后 xIE 置为 0，xPP 置为 y
* xRET 则是指令从状态 x 跳回其他态时使用的 (trap)
  * 例如执行 xRET 时，假设 xPP 的值为 y，那么 xIE 被设为 xPIE，在特权态下转为 y，然后把 xPIE 记为 1，在把 xPP 设为 U (或 M，当 U-mode 不被支持时)

* 一般情况下，xPP 只能在 x 或更低层级的模式下实现，模式为 WARL，同时若 x 层级没有实现则要把对于位置硬连线为 0
* 注：Trap 只能由低层到高层出现



* 

#### 3.

