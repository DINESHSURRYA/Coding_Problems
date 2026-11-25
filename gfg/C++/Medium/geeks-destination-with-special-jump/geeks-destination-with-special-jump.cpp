class Solution {
  public:
    int minTime(int a, int b, int d, int l, int r) {
        static constexpr long long MOD = 1000000007LL;
        long long A = a, B = b, D = d;
        long long net = A - B;   // net distance gained per full cycle
        long long cycle = A + B; // time taken for one full cycle (a + b)

        // Helper: minimum time to reach position >= target without using the special jump
        auto normalTime = [&](long long target) -> long long {
            if (target <= 0) return 0;
            if (target <= A) return target;
            long long k = (target - A + net - 1) / net;
            return k * cycle + (target - k * net);
        };

        // Helper: minimum time to reach position >= target using the special jump of length j
        auto jumpTime = [&](long long j) -> long long {
            return normalTime(D - j) + 1;
        };

        // Normal time without any jump (since r < d, normalTime(D) is always finite)
        long long noJump = normalTime(D);

        // jumpTime(j) is non-increasing as j increases.
        // Find the smallest j in [l, r] where jumpTime(j) < noJump.
        long long lo = l, hi = r, firstBetter = r + 1;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            if (jumpTime(mid) < noJump) {
                firstBetter = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        long long ans = 0;

        // 1. For j in [l, firstBetter - 1], normal movement alone is optimal (or tied)
        if (firstBetter > l) {
            long long cnt = firstBetter - l;
            ans = (ans + (cnt % MOD) * (noJump % MOD)) % MOD;
        }

        // 2. For j in [firstBetter, r], using the jump is strictly faster.
        // Let x = D - j, so x ranges from X_L = D - r to X_R = D - firstBetter.
        if (firstBetter <= r) {
            long long XL = D - r;
            long long XR = D - firstBetter;

            // For x <= A: normalTime(x) + 1 = x + 1
            if (XL <= A) {
                long long upperX = min(XR, A);
                long long firstVal = XL + 1;
                long long lastVal = upperX + 1;
                long long cnt = upperX - XL + 1;

                // Arithmetic progression sum: cnt * (firstVal + lastVal) / 2
                long long s = firstVal + lastVal;
                long long sumAP = ((cnt % 2 == 0) ? ((cnt / 2) % MOD) * (s % MOD)
                                                  : (cnt % MOD) * ((s / 2) % MOD)) % MOD;
                ans = (ans + sumAP) % MOD;
            }

            // For x > A: let rem = x - A, ranging from remL to remR.
            // k = ceil(rem / net), and normalTime(x) + 1 = x + 2*B*k + 1.
            if (XR > A) {
                long long lowerX = max(XL, A + 1);
                long long remL = lowerX - A;
                long long remR = XR - A;

                long long kL = (remL + net - 1) / net;
                long long kR = (remR + net - 1) / net;

                // Sum of (x + 1) across [lowerX, XR]
                long long cntTotal = XR - lowerX + 1;
                long long sX = (lowerX + 1) + (XR + 1);
                long long sumX = ((cntTotal % 2 == 0) ? ((cntTotal / 2) % MOD) * (sX % MOD)
                                                      : (cntTotal % MOD) * ((sX / 2) % MOD)) % MOD;

                // Sum of 2 * B * k grouped by constant k
                long long sumK = 0;
                if (kL == kR) {
                    sumK = ((cntTotal % MOD) * (kL % MOD)) % MOD;
                } else {
                    // First partial block: k = kL, rem in [remL, kL * net]
                    long long firstBlockCnt = kL * net - remL + 1;
                    sumK = (sumK + (firstBlockCnt % MOD) * (kL % MOD)) % MOD;

                    // Last partial block: k = kR, rem in [(kR - 1) * net + 1, remR]
                    long long lastBlockCnt = remR - (kR - 1) * net;
                    sumK = (sumK + (lastBlockCnt % MOD) * (kR % MOD)) % MOD;

                    // Full intermediate blocks: k from kL + 1 to kR - 1, each of length net
                    if (kL + 1 <= kR - 1) {
                        long long numBlocks = (kR - 1) - (kL + 1) + 1;
                        long long sK = (kL + 1) + (kR - 1);
                        long long blockKSum = ((numBlocks % 2 == 0)
                                                   ? ((numBlocks / 2) % MOD) * (sK % MOD)
                                                   : (numBlocks % MOD) * ((sK / 2) % MOD)) % MOD;
                        sumK = (sumK + (net % MOD) * blockKSum) % MOD;
                    }
                }

                long long twoB = (2LL * B) % MOD;
                ans = (ans + sumX + (twoB * sumK) % MOD) % MOD;
            }
        }

        return static_cast<int>(ans);
    }
};