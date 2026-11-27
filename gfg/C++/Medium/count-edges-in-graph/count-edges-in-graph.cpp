class Solution {
  public:
    int countEdges(vector<vector<int>> &adj) {
        int totalDegree = 0;
        for (const auto &neighbors : adj) {
            totalDegree += static_cast<int>(neighbors.size());
        }
        return totalDegree / 2;
    }
};