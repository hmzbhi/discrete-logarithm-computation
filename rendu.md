# TP3

Hamza Bouihi, Bilal Akliai

## Preparatory Work

### Q.1

An optimal algorithm for these constraints is **Pollard's rho algorithm** for discrete logarithms, which has a complexity of $C = O(\sqrt(p))$.

In our case, $p = 2^{115} - 85$, so the cost of such a computation would be approximately $\left(2^{115} - 85\right)^{\frac{1}{2}} \approx 2 \times 10^{17}$ operations. Given that a personal computer can perform $10^{10}$ operations per second, this means that it would take approximately $\approx\dfrac{2\times10^{17}}{10^{10}}$ seconds **$\approx 8$ months** which is not a reasonable time.

### Q.2

For this question, the implementation of `gexp` is in [pollards_kangaroos.c](src/pollards_kangaroos.c) and the test verifying the correctness of our implementation is in [test_gexp.c](test/test_gexp.c).

## Q.3

Here is a detailed explanation of the mul11585 function, which computes $a \times b \mod 2^{115}-85$.

```c
// 2^115 - 85 in hexadecimal: 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFAB
static const num128 mod = {.t = {18446744073709551531ULL, 2251799813685247ULL}};
// 2^115 - 1 in hexadecimal: 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFF
static const num128 m115 = {.t = {18446744073709551615ULL, 2251799813685247ULL}};

/*
 * Multiplies two numbers a and b modulo 2^115 - 85.
 * Inputs: 0 ≤ a, b < 2^115 - 85
 * Output: 0 ≤ ab mod (2^115 - 85) < 2^115 - 85
 */
num128 mul11585(num128 a, num128 b)
{
    // Split a and b into two parts:
    // - a0, b0: lower 64 bits
    // - a1, b1: upper 51 bits
    num128 a0 = {.t = {0, 0}}, a1 = {.t = {0, 0}};
    num128 b0 = {.t = {0, 0}}, b1 = {.t = {0, 0}};
    unsigned __int128 a1b1, a0b1, a1b0, a0b0;
    num128 mid, mid_q = {.t = {0, 0}}, mid_r = {.t = {0, 0}};
    num128 res;

    // Extract lower and upper parts of a and b
    a0.t[0] = a.t[0];  // Lower 64 bits
    a1.t[0] = a.t[1];  // Upper 51 bits
    b0.t[0] = b.t[0];  // Lower 64 bits
    b1.t[0] = b.t[1];  // Upper 51 bits

    // Compute cross-products:
    // a1b1: Product of upper 51 bits of a and b
    // a0b1, a1b0: Mixed products
    // a0b0: Product of lower 64 bits of a and b
    a1b1 = a1.s * b1.s * 696320;  // Adjust for 2^128 mod (2^115 - 85)
    a0b1 = a0.s * b1.s;
    a1b0 = a1.s * b0.s;
    a0b0 = a0.s * b0.s;

    // Reduce a0b0 modulo 2^115 - 85:
    // - Shift out multiples of 2^115 and replace with 85 * (shifted amount)
    // - Keep the remainder in the range 0 ≤ result < 2^115
    a0b0 = ((a0b0 >> 115) * 85) + (a0b0 & m115.s);

    // Compute mid = a0b1 + a1b0 (sum of mixed products)
    mid.s = a0b1 + a1b0;

    // Split mid into high and low parts:
    // - mid_q: Most significant bits, adjusted by multiplying with 696320
    // - mid_r: Least significant bits, reduced modulo 2^115 - 85
    mid_q.t[0] = mid.t[1];      // High 64 bits
    mid_q.s *= 696320;          // Adjust for 2^128 mod (2^115 - 85)
    mid_r.t[1] = mid.t[0];      // Low 64 bits
    mid_r.s = ((mid_r.s >> 115) * 85) + (mid_r.s & m115.s);

    // Sum up all components and reduce modulo 2^115 - 85:
    res.s = a1b1 + a0b0 + mid_q.s + mid_r.s;
    res.s = (res.s >> 115) * 85 + (res.s & m115.s);

    // Final adjustment if result ≥ 2^115 - 85
    res.s = res.s > mod.s ? res.s - mod.s : res.s;

    return res;
}

```

## mplementing kangaroos

### Q.4

In this context, since we are searching for logarithms in the range $[\![0,2^{64}-1]\!]$, we set $\mathcal{W} = 2^{64}$
Based on the heuristic analysis mentioned earlier, we approximate the following values:

- $k \approx \dfrac{log(\mathcal{W})}{2}$
- $\mu \approx \dfrac{\sqrt{\mathcal{W}}}{2}$
- $d \approx \dfrac{log(\mathcal{W})}{\sqrt{\mathcal{W}}}$

Thus, we take:

- $k = 32$
- $\mu = 2^{31}$
- $d = 2^{-26}$

To partition $\mathbb{G}$ into $k$ subsets of approximately equal size, we define:

 $$\mathcal{S}_i = \{g=i[k] | g\in\mathbb{G}\} \text{ for } i \in [\![0,k-1]\!]$$

Next, we define the mapping:
$$\mathcal{J}_i: \mathcal{S}_i \rightarrow \mathbb{G}, x\mapsto xg^{\mu + i} \text{ for } i \in [\![0,k-1]\!]$$

Finally, we define the function $\mathcal{D} as:
$$
\mathcal{D}: x \mapsto
\begin{cases}
      \top & \text{if  $x = 0[d^{-1}]$} \\
      \bot & \text{otherwise}
\end{cases}
$$

### Q.5

For this question, the implementation of `dlog64` is in [pollards_kangaroos.c](src/pollards_kangaroos.c#L53) and the test verifying the correctness of our implementation is in [test_dlog64.c](test/test_dlog64.c).

It achieves high performance through several optimizations:

- Calculating $g^{e_i}$ only once for each $i$, minimizing redundant computations.
- Simultaneously laying new traps while checking for existing ones.
- Utilizing bitwise operations in place of modulo computations for efficiency.

### Q.6

You can evaluate the performance by running [test_perf.c](test/test_perf.c). This will generate a performance footprint, including the number of ticks that measure the complete execution of `dlog64` ( including prints and other non-essential operations).

![Shell-print](/doc/perfs.png "Perfs of dlog64")

On average (10 runs), the algorithm terminates after approximately $3560048283\approx 2^{31.73}$ iterations (where each iteration corresponds to one jump per kangaroo), taking around **$55.71$ seconds** of CPU time. This closely aligns with the expected value of $\sqrt{W} = 2^{32}$, as predicted by the heuristic analysis.

On average, each kangaroo lays about $54$ traps. Consequently, the memory usage is minimal, as we only need to store the position and associated exponent for each trap, along with a few precomputed constants.

### Q.7
