# Theoretical Justification for Noise Testing

# 0. Definitions

- We will denote by $\left(\bold{X}\right)_{c,i,j}$ our original image with dimensions $n\times m$  indexed by $i$ and $j$ and $h$ channels indexed by $c$  ,
- We denote by $\tilde{\bold{X}}$ the noisy version of $\bold{X}$
- Let $N=n\times m\times h$



## 1. Gaussian Noise

### 1.1 Model

We have $\tilde{\bold{X}}_{c,i,j}=\bold{X}_{c,i,j}+\epsilon$ where $\epsilon \sim \mathcal{N}(0,\sigma)$

So we have:
$$
\bold{S}=\sum_{c,i,j}\frac{1}{\sigma^2}(\tilde{\bold{X}}_{c,i,j}-\bold{X}_{c,i,j})^2 \sim \chi²_N
$$

## 1.2 Confidence Interval

let $p\in[0,1].$ we will construct a symmetric interval $\mathcal{I}$  centered at $\mathbb{E}[\bold{S}]=n$ from which  $\mathcal{P}(\bold{S}\notin \mathcal{I})=p$

We will choose $p=10^{-6}$ and we will call it the likelihood limit.

### 1.3 Test

- If the calculated term $\bold{S}\in \mathcal{I}.$ We will say that the result is consistent with the noise model, and it will pass.
- Otherwise, the calculated noise is not consistent with the noise model, and the test will fail within a confidence of $1-p$.



## 2. Impulsive Noise

Inspired from the Wilson score on binomial distribution

## 3. Speckle Noise

Similar to Gaussian Noise test, but with:
$$
\bold{S}=\sum_{c,i,j}\frac{1}{\sigma^2}\left(\frac{\tilde{\bold{X}}_{c,i,j}}{\bold{X}_{c,i,j}}-1\right)^2 \sim \chi²_N
$$
