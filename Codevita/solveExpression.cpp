#include <bits/stdc++.h>
using namespace std;

vector<string> extractBlocks(const vector<string> &lines, int step)
{
  int maxWidth = 0;
  for (auto &r : lines)
    maxWidth = max(maxWidth, (int)r.size());
  vector<string> normalized = lines;
  for (auto &r : normalized)
    if ((int)r.size() < maxWidth)
      r += string(maxWidth - r.size(), ' ');

  int totalCols = maxWidth;
  if (totalCols < 3)
    return {};
  int blockCount = (totalCols + (step - 3)) / step;
  vector<string> blocks;

  for (int i = 0; i < blockCount; ++i)
  {
    int start = i * step;
    string block = "";
    for (int r = 0; r < 3; ++r)
    {
      string row = normalized[r];
      if (start + 3 > (int)row.size())
        row += string(start + 3 - row.size(), ' ');
      block += row.substr(start, 3);
    }
    blocks.push_back(block);
  }
  return blocks;
}

vector<string> detectBlocks(const vector<string> &lines, int expected = -1)
{
  vector<string> blocks4 = extractBlocks(lines, 4);
  vector<string> blocks3 = extractBlocks(lines, 3);

  if (expected > 0)
  {
    if ((int)blocks4.size() == expected)
      return blocks4;
    if ((int)blocks3.size() == expected)
      return blocks3;
  }

  auto countNonEmpty = [](const vector<string> &v)
  {
    int cnt = 0;
    for (auto &p : v)
    {
      bool empty = true;
      for (char ch : p)
        if (ch != ' ')
        {
          empty = false;
          break;
        }
      if (!empty)
        ++cnt;
    }
    return cnt;
  };

  int n4 = countNonEmpty(blocks4), n3 = countNonEmpty(blocks3);
  return (n4 >= n3) ? blocks4 : blocks3;
}

string blockToBinary(const string &block)
{
  string bits;
  for (char c : block)
    bits.push_back(c == ' ' ? '0' : '1');
  return bits;
}

map<string, string> mapPatterns(const vector<string> &lines, const vector<string> &symbols)
{
  vector<string> blocks = detectBlocks(lines, (int)symbols.size());
  map<string, string> patternMap;
  for (size_t i = 0; i < symbols.size() && i < blocks.size(); ++i)
    patternMap[blockToBinary(blocks[i])] = symbols[i];
  return patternMap;
}

vector<string> tokenizeExpression(const vector<string> &lines, const map<string, string> &patterns)
{
  vector<string> blocks = detectBlocks(lines, -1);
  vector<string> tokens;
  string numBuffer = "";

  for (auto &block : blocks)
  {
    string key = blockToBinary(block);
    auto it = patterns.find(key);
    if (it != patterns.end())
    {
      string sym = it->second;
      if (sym.size() == 1 && isdigit(sym[0]))
        numBuffer.push_back(sym[0]);
      else
      {
        if (!numBuffer.empty())
        {
          tokens.push_back(numBuffer);
          numBuffer.clear();
        }
        tokens.push_back(sym);
      }
    }
    else
    {
      bool empty = true;
      for (char c : key)
        if (c != '0')
        {
          empty = false;
          break;
        }
      if (empty)
        continue;
    }
  }
  if (!numBuffer.empty())
    tokens.push_back(numBuffer);
  return tokens;
}

string bitwiseOr(const string &a, const string &b)
{
  int len = max((int)a.size(), (int)b.size());
  string A(len - (int)a.size(), '0');
  A += a;
  string B(len - (int)b.size(), '0');
  B += b;
  string result;
  result.reserve(len);
  for (int i = 0; i < len; ++i)
    result.push_back((A[i] == '1' || B[i] == '1') ? '1' : '0');
  return result;
}

string bitwiseAnd(const string &a, const string &b)
{
  int len = max((int)a.size(), (int)b.size());
  string A(len - (int)a.size(), '0');
  A += a;
  string B(len - (int)b.size(), '0');
  B += b;
  string result;
  result.reserve(len);
  for (int i = 0; i < len; ++i)
    result.push_back((A[i] == '1' && B[i] == '1') ? '1' : '0');
  return result;
}

string bitwiseNot(const string &a)
{
  string result;
  result.reserve(a.size());
  for (char c : a)
    result.push_back(c == '1' ? '0' : '1');
  return result;
}

string numToBinary(const string &num, const map<string, string> &revDigits)
{
  string out;
  for (char ch : num)
  {
    string key(1, ch);
    auto it = revDigits.find(key);
    if (it != revDigits.end())
      out += it->second;
    else
      out += string(9, '0');
  }
  return out;
}

string binaryToNum(const string &bin, const map<string, string> &binToDigit)
{
  if (bin.empty())
    return "0";
  int len = (int)bin.size();
  int rem = len % 9;
  string str = bin;
  if (rem != 0)
    str = string(9 - rem, '0') + str;
  string out;
  for (int i = 0; i < (int)str.size(); i += 9)
  {
    string chunk = str.substr(i, 9);
    auto it = binToDigit.find(chunk);
    out += (it != binToDigit.end()) ? it->second : "0";
  }
  int pos = 0;
  while (pos + 1 < (int)out.size() && out[pos] == '0')
    ++pos;
  return out.substr(pos);
}

string evaluateExpression(const vector<string> &tokens, const map<string, string> &revDigits)
{
  stack<string> values, ops;

  auto apply = [&](const string &op)
  {
    if (op == "~")
    {
      if (values.empty())
      {
        values.push(string(9, '0'));
        return;
      }
      string a = values.top();
      values.pop();
      values.push(bitwiseNot(a));
    }
    else
    {
      if (values.empty())
      {
        values.push(string(9, '0'));
        return;
      }
      string b = values.top();
      values.pop();
      string a = values.empty() ? string(9, '0') : values.top();
      if (!values.empty())
        values.pop();
      if (op == "|")
        values.push(bitwiseOr(a, b));
      else if (op == "&")
        values.push(bitwiseAnd(a, b));
    }
  };

  auto precedence = [&](const string &o) -> int
  {
    if (o == "~")
      return 3;
    if (o == "|")
      return 2;
    if (o == "&")
      return 1;
    return 0;
  };

  for (size_t i = 0; i < tokens.size(); ++i)
  {
    string t = tokens[i];
    if (t == "(")
      ops.push(t);
    else if (t == ")")
    {
      while (!ops.empty() && ops.top() != "(")
      {
        string o = ops.top();
        ops.pop();
        apply(o);
      }
      if (!ops.empty() && ops.top() == "(")
        ops.pop();
    }
    else if (t == "~" || t == "|" || t == "&")
    {
      while (!ops.empty() && ops.top() != "(" && precedence(ops.top()) >= precedence(t))
      {
        string o = ops.top();
        ops.pop();
        apply(o);
      }
      ops.push(t);
    }
    else
      values.push(numToBinary(t, revDigits));
  }

  while (!ops.empty())
  {
    string o = ops.top();
    ops.pop();
    apply(o);
  }

  if (values.empty())
    return string();
  return values.top();
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<string> input(9);
  for (int i = 0; i < 9; ++i)
  {
    if (!getline(cin, input[i]))
      input[i] = "";
  }

  vector<string> digitLines = {input[0], input[1], input[2]};
  vector<string> opLines = {input[3], input[4], input[5]};
  vector<string> exprLines = {input[6], input[7], input[8]};

  vector<string> digits = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  vector<string> ops = {"|", "&", "~", "(", ")"};

  auto digitPatterns = mapPatterns(digitLines, digits);
  auto opPatterns = mapPatterns(opLines, ops);

  map<string, string> revDigits;
  map<string, string> binToDigit;
  for (auto &p : digitPatterns)
  {
    binToDigit[p.first] = p.second;
    revDigits[p.second] = p.first;
  }

  map<string, string> allPatterns = digitPatterns;
  for (auto &p : opPatterns)
    allPatterns[p.first] = p.second;

  auto tokens = tokenizeExpression(exprLines, allPatterns);
  string resultBinary = evaluateExpression(tokens, revDigits);
  string result = binaryToNum(resultBinary, binToDigit);

  cout << result;
  return 0;
}
