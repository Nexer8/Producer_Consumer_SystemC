# The Producer-Consumer problem in SystemC

## Introduction

Task involves creating an app from scratch using SystemC library.

App should implement the standard producer-consumer problem where it is possible to have multiple consumers. Producer and consumers should be connected with the _sc_fifo_ channel.

### Producer should

* generate random integer (from 1,30 range) every _p_ cycles and send it to the consumer(s)
* generate 1000 transactions
* in case of multiple consumers, feed the consumers according to the writing policy - _Round Robin_ or _Load Balancing_

### Consumer should

* read the input number from the producer and wait for _input_ cycles
* print the received input number

## Results

<table>
<tr><th>Round Robin</th><th>Load Balancing</th></tr>
<tr><td>

|#cycles per wait | #consumers | simulation time [ps] |
|-----------------|------------|----------------------|
| 1     | 1    | 105882      |
| 1     | 10   | 19984       |
| 30    | 1    | 3.00588e+06 |
| 30    | 10   | 309984      |

</td><td>

|#cycles per wait | #consumers | simulation time [ps] |
|-----------------|------------|----------------------|
| 1     | 1    | 105882      |
| 1     | 10   | 10601       |
| 30    | 1    | 3.00588e+06 |
| 30    | 10   | 300978      |

</td></tr> </table>

## Conclusions

It is easy to spot that there is no difference in the simulation time when there is only one consumer regardless of the arbitration. That is caused by the fact that there is no way to shorten the waiting time for the consumer to become ready to receive a new message.

However, the higher the number of consumers, the more visible the difference in the simulation time happens to occur. Due to the fact that with _Load Balancing_ the system performs the _wait_ only when all of the consumers are busy processing messages, it was feasible to save some time that would be lost by the _waits_ forcing the sequential order using the _Round Robin_ arbitration.
