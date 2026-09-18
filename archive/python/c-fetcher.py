import json
import urllib.request

s = []
w = []
with urllib.request.urlopen("https://codeforces.com/api/contest.list") as url:
    data = json.loads(url.read().decode())
    for x in data["result"]:
        if x["name"].endswith("(Div. 2)"):
            w.append(x["name"])
            s.append(x["id"])
e = [""]*len(w)

#Edit this line to your handle:
USER_NAME = "immortalfox"

with urllib.request.urlopen("https://codeforces.com/api/user.status?handle="+USER_NAME) as url:
    data = json.loads(url.read().decode())
    for x in data["result"]:
        if "verdict" in x and "contestId" in x:
            if x['verdict'] == 'OK':
                for i in range(0,len(s)):
                    if x["contestId"] == s[i]:
                        e[i] += x["problem"]["index"]
                        break
push = ""
def contest(solved):
  if solved == "":
    return solved
  ans = ""
  done = [""]*30
  counter = 0
  for x in range(0,len(solved) - 1):
    if solved[x] + solved[x + 1] == "C1" or solved[x] + solved[x + 1] == "C2":
      push = solved[x] + solved[x++ + 1]
    elif solved[x] == "C":
      push = solved[x]
    else:
     push = ""
    if push in done:
      push = ""
    done[counter] = push
    counter = counter + 1
    ans += "You solved " + push + "! " if push != "" else ""
  return ans

for i in range(0,len(w)):
  print("#" + str(i+1) + " https://codeforces.com/contest/" + str(s[len(w)-i-1]) + " : " + contest("".join(e[len(w)-i-1])))
