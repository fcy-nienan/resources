**Linux: What is the difference between advisory lock and mandatory lock?**

> https://www.quora.com/Linux-What-is-the-difference-between-advisory-lock-and-mandatory-lock



有些同步的API在单进程中表现正常，但是在多进程中由于看不见，不能达到预期的效果

所以需要外部来协调，通过意向锁来实现