vector<ll> spf_using_simple_sieve(ll n) {
    vector<ll> spf(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        spf[i] = i;
    }
    for (ll i = 2; i * i <= n; i++) {
        if (spf[i] == i) {
            for (ll j = i * i; j <= n; j += i)
                if (spf[j] == j) {
                    spf[j] = i;
                }
        }
    }
    return spf;
}
