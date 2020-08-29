"""
    Problem:

    match strings s and p, where p might contain '.' and '*' symbols

    (this is the first dynamic programming problem I've encountered in Leetcode)

"""


class Solution:

    def isMatch(self, s: str, p: str) -> bool:
        """
        Solution:

        try a dynamic programming formulism

        > problem state
        - use a 2d state of pair (i, j), where i = index in s and j = index in p
        - this is better than the original 1d state I've used where only considered index in p as the state

        > value function
        - define V[i][j] to be the matching result (1 or 0) of string s[:i] and pattern p[:j] (including s[i] and p[j])
        - in original 1d dynamic programming formulism, I used V[i] to represent the index in s where s[:V[i]] matches to 
          pattern p[:j]; but the issues was that V[i] could have multiple values; hence 2d DP formulism is needed

        > Bellman eqn. or update rule or simply a book keeping:
        - every dynamic programming formulism requires a recursive or its equivalent iterative formula to update the value function
        - it's similar to the Bellman eqn. in RL, so I refer to this concept as a Bellman-like eqn or simply an update rule
        - it is preferrable to express the update rule in iterative format than in recursive format
        - for this problem, the update rule could be expressed as follows:
            - first initialize every entry of V to be zero

            - at any index i and j:

                - if p[j+1] does not exist or p[j+1] is not a '*'
                    - the only scenario that leads to a match is if the following conditions are satisfied simultaneously:
                        - p[j] is a '.' or that p[j] equal to s[i]
                        - we already know that s[:i-1] matches to p[:j-1], or that V[i-1][j-1] = 1
                        
                        we could determine then that s[:i] also matches to p[:j]
                        or that
                            V[i][j] = 1 if V[i-1][j-1]

                - if p[j+1] does exist and it is a '*':
                    now there are several scenarios in which we need to update the value function
                    
                    case-a): if we know s[:i-1] matches to p[:j-1], it immediately follows that s[:i-1] matches to p[:j+1]
                        - this is because '.*' or 'a*' can always be matched to an empty string
                        or that
                            V[i-1][j+1] = 1 if V[i-1][j-1]

                    case-b): also, if we know s[:i] matches to p[:j-1], it immediately follows that s[:i] also matches to p[:j+1]
                        - this is because of the same reason as in case-a)
                        or that
                            V[i][j+1] = 1 if V[i][j-1]

                        note that neither of the two cases so far requires any knowledge of the relationship between s[i] and p[j]

                    case-c): if p[j] matches to s[i] by either being the same character or by being the wild card '.'
                        - there are several conclusions following this scenario:

                            - if we know s[:i-1] matches to p[:j-1] then by definition we know s[:i] matches to p[:j]
                            - we also know by definition that s[:i] matches to p[:j+1]
                            - both of the two results require that '*' be matched to repeat the preceding element exactly once
                            or that
                                V[i][j] = 1, V[i][j+1] = 1 if V[i-1][j-1]
                            
                            - if we know s[:i-1] matches to p[:j+1], we can always know s[:i] matches to p[:j+1]
                            - this might look redundant, but this is a different case than previous one, because in this case we
                              require that '*' be matched to repeat more than once; actually in this case, should iterate over s
                              until the condition breaks, until then we can keep increasing i and updating the value function
                              or that:
                                while (the condition holds):
                                    V[i][j+1] = 1 if V[i-1][j+1]
                                    i += 1

            > value iteration:
            - any dynamic programming requires an iteration over the problem states to reach final state
            - or in recursive format, a recursion; but there will always be an equivalent iterative version of the recursion
            - here the iteration could be very straightforward, just a nested for-loops over j and i
            - in each iteration, we apply the aforementioned update rule to maintain a book keeping of the value function
            or that
                for j in len(p)
                    for i in len(s)
                        update V according to the case rules

            > initial conditions
            - if we iterate from head to tail of the two strings, we need to initialize V for the cases where i==0 or j==0
            - unfortunately, there isn't a simple way to do so without altering the update rule's code heavily
            - in the end I opted to add a redundant row and column in the value function V, where
                for V[:][0] and V[0][:] all equal to zero, except that V[0][0] is initialized to 1
            - this means that when matching the first characters from the two strings, we implicity assumed that the 'zero-th' characters of the two strings,
              which can be interpretted as empty characters, are implicitly considered to be a match (thus V[0][0] = 1), but the zero-th characters matching with any other
              character in either of the strings are initialized to zero because the algorithm still needs to look at the cases
            - by this method no need to alter the codes except that from now on, index j for the pattern location is index j+1 for the corresponding value, same for i

            > policy control or back-track to the solution
            - once the value iteration finishes, needs a way to back-track from the value functions to the desired format of the solution
            - in analogy to RL, this is the process of policy control or to obtain the policy function from the computed value function
            - here it is straight-forward, just return the final state value as the result
              or that
                return V[len(s)][len(p)]

            
            other considerations:
            - need to consider cases where either or both s and p is empty
            - take note that '.' doesn't match to empty character; this could only be possible if a character is followed by '*' and interpretted as repeating zero times

        """

        V = [[0 for i in range(len(p)+1)] for i in range(len(s)+1)]
        V[0][0] = 1

        # if s is empty
        if not s:
            # if p is also empty, return match
            if not p:
                return True
            # if p is not empty
            else:
                # iterate over p
                for j in range(0, len(p)):

                    # if p[j+1] exists and it is '*'
                    # if p[:j-1] is matched to empty string
                    # then p[:j+1] is also matched to empty string
                    if j+1 < len(p) and p[j+1] == '*' and V[0][j]:
                        V[0][j+2] = 1


        # if s is not empty
        else:
            # if p is empty, return mismatch
            if not p:
                return False
            # if neither s nor p is empty
            else:

                # iterate over p
                for j in range(0, len(p)):
                    # iterate over s
                    for i in range(0, len(s)):

                        # p[j] is last element in p or p[j+1] is not '*'
                        if j+1 == len(p) or p[j+1] != '*':
                            if((p[j] == s[i] or p[j] == '.')):
                                if V[i][j]:
                                    # if s[:i-1] matches p[:j-1], then s[:i] matches p[:j] 
                                    V[i+1][j+1] = 1

                        # p[j+1] is '*'
                        else:
                            # if s[:i] matches p[:j-1], then s[:i] always matches p[:j+1]
                            # or if s[:i-1] matches p[:j-1], then s[:i-1] always matches p[:j+1]
                            # because '.*' or 'a*' can always match to empty string by repeating '*' zero times
                            if V[i+1][j]:
                                V[i+1][j+2] = 1
                            if V[i][j]:
                                V[i][j+2] = 1
                            # if p[j] matches s[i] by being '.' or equal letter
                            while(i < len(s) and (p[j] == s[i] or p[j] == '.')):
                                # if s[:i-1] matches p[:j-1], then s[:i] matches p[:j]
                                # and s[:i] also matches p[:j+1] because '*' can repeat exactly once
                                if V[i][j]:
                                    V[i+1][j+1] = 1
                                    V[i+1][j+2] = 1
                                # if s[:i-1] matches p[:j+1], then s[:i] always matches p[:j+1] as i increases
                                # because s[i] == p[j] or p[j] == '.', and '*' can be repeated more than once
                                if V[i][j+2]:
                                    V[i+1][j+2] = 1

                                i += 1

        # return final state value as the solution
        return V[len(s)][len(p)]




if __name__ == '__main__':
    sol = Solution()
    s = 'aab'
    p = 'c*a*b'
    print(sol.isMatch(s,p))





                


