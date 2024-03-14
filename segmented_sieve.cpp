typedef long long ll;

// used for getting primes in a specific range L to R
vector<bool> segmented_sieve(ll L, ll R) {
    ll lim = sqrt(R);
    vector<bool> mark(lim + 1, false);
    vector<ll> primes;
    for (ll i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (ll j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    vector<bool> is_prime(R - L + 1, true);
    for (ll i : primes)
        for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            is_prime[j - L] = false;
    if (L == 1)
        is_prime[0] = false;
    // provides is_prime[x]=true for all x<=1
    return is_prime;
}
