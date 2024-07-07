// shawdow orz

const ll ALPHABET = 26;
struct trie {

      // ll ans = 0;

      struct node {
            bool ends;
            ll st_cnt; // subtree size / count
            array<node*, ALPHABET> next;
            
            node() {
                  ends = false;
                  for(ll i = 0; i < 26; i++) {
                        next[i] = NULL;
                  }
                  st_cnt = 0;
            }
      };

      inline int where(char c) {
            return c - 'a';
      }

      node *head = NULL;
      trie() {
            head = new node();
      }

      void insert(const string &s) {
            node *curr = head;

            for(ll i = 0; i < (ll)s.size(); i++) {
                  curr->st_cnt++;
                  
                  ll x = where(s[i]);

                  if(curr->next[x] == NULL) {
                        curr->next[x] = new node();
                  }

                  curr = curr->next[x];
                  // ans += curr->st_cnt;
            }

            curr->st_cnt++;
            curr->ends = true;
      }

      bool find(const string& s) {
            node *curr = head;

            for(ll i = 0; i < (ll)s.size(); i++) {
                  ll x = where(s[i]);
                  if(curr->next[x] == NULL) {
                        return false;
                  }
                  curr = curr->next[x];
            }

            return curr->ends;
      }

      void erase(const string& s) { // must be present
            node *curr = head;

            for(ll i = 0; i < (ll)s.size(); i++) {
                  curr->st_cnt--;
                  
                  ll x = where(s[i]);

                  if(curr->next[x] == NULL) {
                        assert(false);
                  }

                  curr = curr->next[x];
            }

            curr->st_cnt--;
            if(curr->st_cnt == 0) { // there might be duplicate elements. so erase only if it is the last element leftover.
                  curr->ends = false;
            }
      }

      ll prefix(const string& s) { // number of strings that have s as prefix
            node *curr = head;
            for(ll i = 0; i < (ll)s.size(); i++) {
                  ll x = where(s[i]);
                  if(curr->next[x] == NULL) {
                        return 0;
                  }
                  curr = curr->next[x];
            }
            return curr->st_cnt;
      }

      void delt(node *curr) {
            if(curr == NULL) {return;}
            for(ll i = 0; i < 26; i++) {
                  delt(curr->next[i]);
            }
            delete curr;
      }

      ~trie() {
            delt(head);
      }
};
// trie T;
// T.insert(s);

// https://leetcode.com/problems/design-add-and-search-words-data-structure/description/
// code snippet for the above question: [search for "[..abc..pq]" matches. (where '.' could be any letter.)]

// dfs type recursive function for that:
    // bool find(node* curr, const string& s, ll idx) {
    //     ll n = (ll)s.size();
    //     if(idx == n) {
    //         return curr->ends;
    //     }
    //     bool ans = false;
    //     if(s[idx] == '.') {
    //         for(ll x = 0; x < 26; x++) {
    //             if(curr->next[x] == NULL) {
    //                 // take lite.
    //             } else {
    //                 ans |= find(curr->next[x], s, idx+1);
    //             }
    //         }
    //     } else {
    //         ll x = where(s[idx]);
    //         if(curr->next[x] == NULL) {
    //             ans = false;
    //         } else {
    //             ans = find(curr->next[x], s, idx+1);
    //         }
    //     }
    //     return ans;
    // }




// ================================================================================================
// [og version:]
const int ALPHABET = 26;
struct trie{
	struct node{
		bool ends;
		int sub;
		array<node*,ALPHABET> next;
		node(){
			ends = false;
			for(int i = 0; i < 26; i++){
				next[i] = NULL;
			}
			sub = 0;
		}
	};
	
	inline int where(char c){
		return c - 'a';
	}
	
	node *head = NULL;
	trie(){
		head = new node();
	}
	void insert(const string &s){
		node *cur = head;
		for(int i = 0; i < (int)s.size(); i++){
			cur->sub++;
			int x = where(s[i]);
			
			if(cur->next[x] == NULL){
				cur->next[x] = new node();
			}
			cur = cur->next[x];
		}
		cur->sub++;
		cur->ends = true;
	}
	
	bool find(const string &s){
		node *cur = head;
		for(int i = 0; i < (int)s.size(); i++){
			int x = where(s[i]);
			if(cur->next[x] == NULL){
				return false;
			}
			cur = cur->next[x];
		}
		return cur->ends;
	}
	
	void erase(const string &s){ // Must be present
		node *cur = head;
		for(int i = 0; i < (int)s.size(); i++){
			cur->sub--;
			int x = where(s[i]);
			cur = cur->next[x];
		}
		cur->sub--;
		if(cur->sub == 0){
			cur->ends = false;
		}
	}
	
	int prefix(const string &s){ // Number of strings which have s as prefix
		node *cur = head;
		for(int i = 0; i < (int)s.size(); i++){
			int x = where(s[i]);
			if(cur->next[x] == NULL){
				return 0;
			}
			cur = cur->next[x];
		}
		return cur->sub;
	}
	
	void delt(node *cur){
		if(cur == NULL)return;
		for(int i = 0; i < 26; i++){
			delt(cur->next[i]);
		}
		delete cur;
	}
	
	~trie(){
		delt(head);
	}
};
