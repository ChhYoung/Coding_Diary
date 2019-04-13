
# <center> 机器学习实验报告 <center>

  <br/><br/><br/><br/>

  <br/><br/><br/><br/>
  <br/><br/><br/><br/>
### <center> 姓名：杨崇焕
### <center> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;学号：U201610531
### <center> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;班级：电信中英1601
### <center> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;实验内容：神经网络和回归分析
  <br/><br/><br/><br/>
    <br/><br/><br/><br/>
      <br/><br/><br/><br/>
        <br/><br/><br/><br/>
<div STYLE="page-break-after: always;"></div>

### 一.实验目的：
任务一：使用 Logistic 回归估计马疝病的死亡率
任务二：使用神经网络完成新闻分类
### 二.实验原理：
**Logistic 回归：** 预测函数如下：
$$ h(x)=\frac{1}{1+e^{-w^Tx}}
$$&emsp;&emsp;&emsp;&emsp;&emsp;其预测值 h(x) 仍为连续区间 (0,1) 上的某个值。处理方法是确定一个阈值 ϵ，使得
&emsp;&emsp;&emsp;&emsp;&emsp;h(x) ≥ ϵ predict: y = 1
&emsp;&emsp;&emsp;&emsp;&emsp;h(x) < ϵ predict: y = 0
&emsp;&emsp;&emsp;&emsp;&emsp;用线性回归模型的预测结果去逼近真实标记的对数几率，是一种分类方法
**神经网络：** 较复杂，详细见[wiki](https://en.wikipedia.org/wiki/Artificial_neural_network)

### 三.实验过程：
#### - 实验环境：
&emsp;&emsp;&emsp;- ubuntu 18.04
&emsp;&emsp;&emsp;- python 3.6
&emsp;&emsp;&emsp;- numpy 1.14.3
&emsp;&emsp;&emsp;- pandas 0.23.0
&emsp;&emsp;&emsp;- scikit-learn 0.19.1
&emsp;&emsp;&emsp;- pytorch 1.0.1.post2 
&emsp;&emsp;&emsp;- cuda 9.0.176

#### - 任务一：使用 Logistic 回归估计马疝病的死亡率
