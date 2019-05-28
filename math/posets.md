Paritally Ordered Sets
====================

Source: *Principals of Program Analysis* -- Nielson and Nielson

Index
----------------
1. [Basic Definitions](#basics)


Basic Definitions
--------------------

### Partial Ordering

A *partial ordering* is a relation: $\sqsubseteq: L \times L \rightarrow \\{true, false\\}$ with the following properties,

* it is *reflexive*, i.e. $\forall{}l: l \sqsubseteq{} l$.
* it is *anti-symmetric*, i.e. $\forall{}l_1,l_2: l_1 \sqsubseteq l_2 \wedge l_2 \sqsubseteq l_1 \Rightarrow l_1 = l_2$.
* it is *transitive*, i.e. $\forall{}l_1,l_2,l_3: l_1 \sqsubseteq l_2 \wedge l_2 \sqsubseteq l_3 \Rightarrow l_1 \sqsubseteq l_3$.

Note: It is a *relation* and not a *function* since it may not apply to all the values in the domain (every pre-image may not have an image).

### Partially Ordered Set (poset)

A *partially ordered set* $(L, \sqsubseteq)$ is a set $L$ equipped with a partial ordering $\sqsubseteq$ (sometimes written $\sqsubseteq_L$).


   
<div class="footer">
<br/>
&copy; Anshuman Dhuliya
<br/>
</div>

