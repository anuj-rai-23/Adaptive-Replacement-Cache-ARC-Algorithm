# Adaptive Replacement Cache (ARC) Algorithm
A project for Advanced Operating System(CS604) that implements ARC cache replacement policy.</br>
Refer to paper [Outperforming LRU with an adaptive replacement cache algorithm](https://ieeexplore.ieee.org/document/1297303)</br>
Project done under supervision of [Dr. Nitin Auluck](https://sites.google.com/iitrpr.ac.in/nauluck)

## Implementation
Four primary lists:
<ol>
<li> MRU(T1) contains the top or most-recent pages in L1 </li>
<li> MRUG(B1) contains the bottom or least-recent pages in L1 </li>
<li> MFU(T2)  contains the top or most-recent pages in L2 </li>
<li> MFUG(B2) contains the bottom or least-recent pages in L2 </li>
</ol>

*Size of these lists is controlled by parameter p, which controls the ratio of sizes between most-recent and least-recent pages*</br>
Implemented in C++ using containers from **Standard Template Library(STL)**


## Results
ARC outperforms LRU in terms of hit-ratio and execution time (calculated in sec.)</br>
See [Result Graphs](/Graphs)
<img src="/Graphs/P1_Time.png" alt="Execution Time" width="300"/>
<img src="/Graphs/P1_Ratio.png" alt="Execution Time" width="300"/>
