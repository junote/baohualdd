|mutex/Semaphore|Spinlock|
|-|-|
|Used when the task can sleep while waiting for the lock.|Used when the task can’t sleep while waiting for the lock.|
|It can be held for a long duration of time.	|It can be held for a short duration of time.|
|It can only be used in process context, not in interrupt context.	|It can only be used in the Interrupt context, not in the Process context.|
|High overhead locking.|	Low overhead locking.|