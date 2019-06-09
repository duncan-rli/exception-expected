Having recenlty seen the Herb Sutter presentation on Lightweight exception handling then finding Simon Brand's "Functional exceptionless error handling with std::expected" article (https://github.com/TartanLlama/expected), I wondered how timings for them would compare.

Using Simon Brand's example as a base, the test functions create an array of smart pointers, then destroys them.  Each test has three functions. Test 1 has no errors and all three functions are executed.  Test 2 has an error in the first function, Test 3 has an error in the second function and Test 4 has an error in the last function.

The Normal Group use std::expected to return the error, the Monad Group use std::expected with the ".and_then" extension.
The SEH Group uses exceptions.

Without exceptions enabled

Using visual code in a VM, compiler flags clang++ -std=c++17 -stdlib=libc++ -fno-exceptions expecttest.cpp -o expecttest.out --debug 

Normal
Test 1 min: 2670      max: 53189      avg: 2935       count: 1000     pmax: 3722      pavg: 2875      pc: 998
Test 2 min: 589       max: 1485       avg: 699        count: 1000     pmax: 1485      pavg: 699       pc: 1000
Test 3 min: 1137      max: 5317       avg: 1274       count: 1000     pmax: 1457      pavg: 1269      pc: 999
Test 4 min: 1667      max: 15989      avg: 1838       count: 1000     pmax: 2877      pavg: 1824      pc: 999
Monad
Test 1 min: 2732      max: 25456      avg: 2977       count: 1000     pmax: 3971      pavg: 2947      pc: 996
Test 2 min: 726       max: 7525       avg: 823        count: 1000     pmax: 1039      pavg: 817       pc: 999
Test 3 min: 1243      max: 2690       avg: 1402       count: 1000     pmax: 2690      pavg: 1402      pc: 1000
Test 4 min: 1741      max: 6288       avg: 1914       count: 1000     pmax: 2822      pavg: 1902      pc: 997



With exceptions enabled

Using visual code in a VM, compiler flags clang++ -std=c++17 -stdlib=libc++ expecttest.cpp -o expecttest.out --debug


Normal
Test 1 min: 2525      max: 9409       avg: 2867       count: 1000     pmax: 3357      pavg: 2857      pc: 998
Test 2 min: 551       max: 11023      avg: 696        count: 1000     pmax: 1641      pavg: 680       pc: 998
Test 3 min: 1026      max: 1485       avg: 1222       count: 1000     pmax: 1485      pavg: 1222      pc: 1000
Test 4 min: 1537      max: 3204       avg: 1752       count: 1000     pmax: 3204      pavg: 1752      pc: 1000
Monad
Test 1 min: 2639      max: 9568       avg: 3013       count: 1000     pmax: 3458      pavg: 3003      pc: 996
Test 2 min: 691       max: 1005       avg: 807        count: 1000     pmax: 1005      pavg: 807       pc: 1000
Test 3 min: 1176      max: 5972       avg: 1380       count: 1000     pmax: 2321      pavg: 1372      pc: 998
Test 4 min: 1616      max: 10988      avg: 1889       count: 1000     pmax: 2348      pavg: 1871      pc: 997
SEH
Test 1 min: 2510      max: 253491     avg: 3504       count: 1000     pmax: 3984      pavg: 2922      pc: 969
Test 2 min: 2704      max: 248603     avg: 4021       count: 1000     pmax: 3755      pavg: 2879      pc: 930
Test 3 min: 3207      max: 867992     avg: 4783       count: 1000     pmax: 3966      pavg: 3435      pc: 927
Test 4 min: 3837      max: 874284     avg: 6451       count: 1000     pmax: 3999      pavg: 3943      pc: 332


min - minimum time taken
max - maximum time taken
avg - average time take
count - number of times test repeated
pmax - max time taken ignoring large values
pavg - average time ignoring large value
pc - number of repeats included when large values ignored



Conclusion
On a virtual box running linux Mint there is alot of variation.  Occasionally things can take a lot longer, especially the first run through a loop.  Having exceptions enabled generaly increases the average times, using exceptions really increases the average times.  Pretty much as expected.  The use of std::expected increases times marginally but is concise, easy to read and errors cannot be ignored and finding that out was really the point of all this.





