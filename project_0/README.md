### The machine I am running on had the following specifications:
```
Operating System: GNU/Linux, Linux Mint 19.3 Tricia  
CPU 		: Intel(R) Core(TM) i5-4200M CPU @ 2.50GHz
```

### The Performance Results I got were:

Using 4 threads  
`Peak Performance =   875.14 MegaMults/Sec`  

for the values -
```
SIZE	: 32768  
NUMTRIES: 100
```
**Note**: _I tested with bigger values like 65536 and 500 tries and still got a Peak Performance of ~860 MegaMults/Sec._  


### Speedup Fraction:

```
Peak Performance with 1 thread : 369.32 MegaMults/Sec  
Peak Performance with 4 threads: 875.14 MegaMults/Sec  

Speedup Fraction(S) = 875.14/369.32 
		    = 2.35  
```

**Note**: _I would fairly occasionally (approx. 1 in 8) get Peak Performance on 1 thread as ~270 MegaMults/Sec. Using that value would result in a Speedup Fraction of 3.24 which is significantly greater than the currently obtained value of 2.35; I was wondering what might be the cause of such occasional discrepancy._  

As for the question of why the speedup is less than 4.0, I am assuming it is because of the overhead of creating additional threads (i.e. maintaining the state for each thread). To test this hypothesis, I intend to rerun the program with 2, and 8 threads while keeping SIZE and NUMTRIES the same. I expect the Speedup Fraction for 2 threads to be close to 2.0 while the Speedup Fraction for 8 threads will be far lesser than 8.0; my guess is based on the overhead cost on maintaining less/more threads.  

#### Results: 

For 2 threads, the Peak Performance fluctuates greatly, ranging from 450-710 MegaMults/Sec

`Peak Performance = 1.22-1.92 MegaMults/Sec`  

For 8 threads, the Peak Performance averages around 550-650 MegaMults/Sec

`Peak Performance = 1.49-1.76 MegaMults/Sec`  

**Note**: _While the conclusion seems to support my hypothesis that the overhead cost of each additional thread is significant, I have extremely limited knowledge on the subject matter and could just be misattributing the results._  


### Parallel Fraction:

```
Fp = (4.0/3.0)*(1.0 - (1.0/S)) 
   = 0.76596
```





