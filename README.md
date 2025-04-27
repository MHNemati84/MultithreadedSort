# About
In this Mini-Project the aim is to demonstrate one of the many computational problems that threads
can help us solve: Sorting

Given an input array `input`. The array is split into two halves, left and right.
One thread is associated per each half to sort the elements in the respective half.
After being done with the individual halves, we use a third thread `merge_thread` to merge
the two halves into the `output` array.
