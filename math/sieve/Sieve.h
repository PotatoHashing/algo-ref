template <int SZ>
class Sieve {
 public:
  vector<int> primes, spf;  // smallest prime factor
  constexpr Sieve() : primes(), spf(SZ, 0) {
    for (int i = 2; i < SZ; i++) {
      if (!spf[i]) primes.push_back(i), spf[i] = i;
      for (int j = 0; j < primes.size() && i * primes[j] < SZ; j++) {
        spf[i * primes[j]] = primes[j];
        if (spf[i] == primes[j]) break;
      }
    }
  }
};