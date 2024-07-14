// pre stores the nearest previous ***index*** that had a smaller element
// suf stores the nearest next ***index*** that has a smaller element.
      auto prev_smaller = [&](vector<ll>& b) -> vector<ll> {
            ll N = (ll)b.size();
            vector<ll> ans(N, 0);
            vector<array<ll, 2>> Stack;
 
            for(ll i = 0; i < N; i++) {
                  while(Stack.empty() == false && Stack.back()[1] >= b[i]) {
                        Stack.pop_back();
                  }
                  if(Stack.empty()) {
                        ans[i] = 0;
                  } else {
                        ans[i] = Stack.back()[0];
                  }
                  Stack.push_back({i+1, b[i]});
            }
 
            return ans;
      };
 
      auto pre = prev_smaller(a);
      auto a_copy = a;
      reverse(a_copy.begin(), a_copy.end());
      auto suf = prev_smaller(a_copy);
 
      reverse(suf.begin(), suf.end());
      for(auto &x : suf) {
            x = n + 1 - x;
      }
