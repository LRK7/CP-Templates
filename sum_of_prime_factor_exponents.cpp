vector<ll> simple_sieve(ll n) {
    vector<bool> is_prime(n + 1, true);
    vector<ll> prime_list;
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    for (ll i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime_list.push_back(i);
        }
    }
    return prime_list;
}

ll sum_of_prime_factor_exponents(ll n) {
    ll cnt = 0;
    for (ll i = 0; i < p_list.size(); ++i) {
        if (p_list[i]*p_list[i] > n) {break;}
        if (n % p_list[i] == 0) {
            while (n % p_list[i] == 0) {
                n /= p_list[i];
                cnt++;
            }
        }
    }
    if (n > 1) {
        cnt++;
    }
    return cnt;
}
