

struct trie {
      static const ll B = 30;
      struct node {
            // bool ends; // unnecssary in bit trie
            ll st_cnt;
            array<node*, 2> next;
 
            node() {
                  for(ll i = 0; i < 2; i++) {
                        next[i] = NULL;
                  }
                  st_cnt = 0;
            }
      };
 
      node *head = NULL;
      trie() {
            head = new node();
      }
 
      void insert(ll val) {
            node *curr = head;
 
            for(ll i = B; i >= 0; i--) {
                  curr->st_cnt++;
 
                  ll bit = val >> i & 1;
 
                  if(curr->next[bit] == NULL) {
                        curr->next[bit] = new node();
                  }
 
                  curr = curr->next[bit];
                  // ans += curr->st_cnt;
            }
 
            curr->st_cnt++;
      }
 
      void erase(ll val) {
            node *curr = head;
            for(ll i = B; i >= 0; i--) {
                  curr->st_cnt--;
                  ll bit = val >> i & 1;
                  if(curr->next[bit] == NULL) {
                        assert(false);
                  }
                  curr = curr->next[bit];
            }
            curr->st_cnt--;
      }
 
      ll query(ll x, ll k) { 
      // number of values s.t. val ^ x < k
            node* curr = head;
            ll ans = 0;
            
            for(ll i = B; i >= 0; i--) {
                  if(curr == NULL) {break;}
 
                  ll x_bit = x >> i & 1;
                  ll k_bit = k >> i & 1;
 
                  if(k_bit == 1) {
                        if(curr->next[x_bit] != NULL) {
                              ans += curr->next[x_bit]->st_cnt;
                        }
                        curr = curr->next[x_bit ^ 1];
                  } else {
                        // k == 0; 
                        // so we can only choose those vals
                        // .. that has to be same bit as x.
                        curr = curr->next[x_bit];
                  }
            }
 
            return ans;
 
      }
 
      // ll helper = 0;
 
      ll get_max(ll x) {
      // returns maximum of val ^ x
            node* curr = head;
            ll ans = 0;
            // helper = 0;
            for(ll i = B; i >= 0; i--) {
                  ll x_bit = x >> i & 1;
                  if(curr->next[x_bit ^ 1] != NULL && curr->next[x_bit ^ 1]->st_cnt > 0) {
                        curr = curr->next[x_bit ^ 1];
                        ans <<= 1;
                        ans++;
 
                        // helper <<= 1;
                        // helper += (x_bit ^ 1);
                  } else {
                        curr = curr->next[x_bit];
                        ans <<= 1;
 
                        // helper <<= 1;
                        // helper += (x_bit);
                  }
            }
            return ans;
      }
 
      ll get_min(ll x) {
      // returns minimum of val ^ x
            node* curr = head;
            ll ans = 0;
            for(ll i = B; i >= 0; i--) {
                  ll x_bit = x >> i & 1;
                  if(curr->next[x_bit] != NULL && curr->next[x_bit]->st_cnt > 0) {
                        curr = curr->next[x_bit];
                        ans <<= 1;
                  } else {
                        curr = curr->next[x_bit ^ 1];
                        ans <<= 1;
                        ans++;
                  }
            }
            return ans;
      }
 
      void delt(node* curr) {
            if(curr == NULL) {return;}
            for(ll i = 0; i < 2; i++) {
                  delt(curr->next[i]);
            }
            delete curr;
      }

      // keeping the destructor commented makes it work. when it was uncommented T.~trie() wasnt working
      // use T.delt(T.head) instead.
      // ~trie() {
      //       delt(head);
      // }
};
// trie T;
// T.insert(x);

// https://www.spoj.com/status/SUBXOR,dabest/
