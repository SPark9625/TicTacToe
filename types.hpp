#ifndef types_hpp
#define types_hpp

#include <torch/torch.h>


using Board = torch::Tensor;
using Action = typename std::tuple<int,int,int>;
using ID = typename std::vector<Action>;

using Reward = torch::Tensor;
using Policy = torch::Tensor;

using State = typename std::tuple<ID, Board>;


#endif // types_hpp
