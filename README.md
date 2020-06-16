As Linus Torvalds wrote in his commit
>Many load balancing and workload placing programs check /proc/meminfo to estimate how much free memory is available.  They generally do this by adding up "free" and "cached", which was fine ten years ago, but is pretty much guaranteed to be wrong today.

full commit message: `https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=34e431b0ae398fc54ea69ff85ec700722c9da773`

So he wrote his own modern estimate called MemAvailable.
>Currently, the amount of memory that is available for a new workload, without pushing the system into swap, can be estimated from MemFree, Active(file), Inactive(file), and SReclaimable, as well as the "low" watermarks from /proc/zoneinfo.

I tested allocation of 
 - free
 - free + 1 MB
 - available
 - available + 1 MB
 - free + cached
 - free + cached + 1 MB

All tests were successful on my machine. The reason why even "`free + cached + 1 MB`" was successful is due to other memory being pushed into swap. So it is often possible to allocate more then aforementioned estimates, but the system will perform worse if we do that.