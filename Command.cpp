#include "Command.h"
#include "OrderBookEntry.h"
#include "AdvisorBot.h"
#include "OrderBook.h"
#include <iostream>

Command::Command(OrderBook _orderBook,
                 std::string _currentTime,
                 std::string _cmd)
    : orderBook(_orderBook),
      currentTime(_currentTime),
      cmd(_cmd)
{
}
Command::Command(OrderBook _orderBook,
                 std::string _currentTime,
                 std::string _cmd,
                 std::string _arg1)
    : orderBook(_orderBook),
      currentTime(_currentTime),
      cmd(_cmd),
      arg1(_arg1)
{
}
Command::Command(OrderBook _orderBook,
                 std::string _currentTime,
                 std::string _cmd,
                 std::string _arg1,
                 OrderBookType _arg2,
                 std::string _order)
    : orderBook(_orderBook),
      currentTime(_currentTime),
      cmd(_cmd),
      arg1(_arg1),
      arg2(_arg2),
      order(_order)
{
}
Command::Command(OrderBook _orderBook,
                 std::string _currentTime,
                 std::string _cmd,
                 std::string _arg1,
                 OrderBookType _arg2,
                 std::string _order,
                 std::string _arg3)
    : orderBook(_orderBook),
      currentTime(_currentTime),
      cmd(_cmd),
      arg1(_arg1),
      arg2(_arg2),
      order(_order),
      arg3(_arg3)
{
}

void Command::invoke()
{
    if (cmd == "help")
    {
        if (!arg1.empty())
        {
            helpCmd(arg1);
            return;
        }
        help();
    }

    if (cmd == "prod" && arg1.empty())
    {
        prod(orderBook);
    }
    if (cmd == "min" && !order.empty())
    {
        min(orderBook, arg1, arg2, currentTime, order);
    }
    if (cmd == "max" && !order.empty())
    {
        max(orderBook, arg1, arg2, currentTime, order);
    }
    if (cmd == "avg" && !arg3.empty())
    {
        avg(orderBook, arg1, arg2, arg3, currentTime, order);
    }
    if (cmd == "predict" && !arg3.empty())
    {
        predict(orderBook, arg1, arg2, arg3, currentTime, order);
    }
    if (cmd == "time" && arg1.empty())
    {
        time(currentTime);
    }
    if (cmd == "step" && arg1.empty())
    {
        currentTime = step(orderBook, currentTime);
    }
    if (cmd == "import" && !arg1.empty())
    {
        orderBook = import(arg1);
        currentTime = orderBook.getEarliestTime();
    }
}

void Command::help()
{
    AdvisorBot::welcomePrompt();
}

void Command::helpCmd(std::string command)
{
    if (command == "prod")
    {
        std::cout << "prod:    list available products" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "user$ prod" << std::endl;
        std::cout << "advisorbot$ ETH/BTC DOGE/BTC" << std::endl;
    }
    if (command == "min")
    {
        std::cout << "min <product> <order>:    find minimum <order> for <product> in current time step" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "user$ min ETH/BTC ask" << std::endl;
        std::cout << "advisorbot$ The min ask for ETH/BTC is 1.0" << std::endl;
    }
    if (command == "max")
    {
        std::cout << "max <product> <order>:    find maximum <order> for <product> in current time step" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "user$ max ETH/BTC ask" << std::endl;
        std::cout << "advisorbot$ The max ask for ETH/BTC is 1.0" << std::endl;
    }
    if (command == "avg")
    {
        std::cout << "avg <product> <order> <timesteps>:    compute average <order> for the sent <product> over the sent number of <timesteps>" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "user$ avg ETH/BTC ask 10" << std::endl;
        std::cout << "advisorbot$ The average ETH/BTC ask price over the last 10 timesteps was 1.0" << std::endl;
    }
    if (command == "predict")
    {
        std::cout << "predict <max/min> <order> <product>:    predict <max> or <min> and <order> for the sent <product> for the next time step" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "user$ predict max ETH/BTC bid" << std::endl;
        std::cout << "advisorbot$ The average ETH/BTC ask price over the last 10 timesteps was 1.0" << std::endl;
    }
    if (command == "time")
    {
        std::cout << "time:    state current time in dataset, i.e. which timeframe are we looking at" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "user$ time" << std::endl;
        std::cout << "advisorbot$ 2020/03/17 17:01:24" << std::endl;
    }
    if (command == "step")
    {
        std::cout << "step:    move to next time step" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "user$ step" << std::endl;
        std::cout << "advisorbot$ Now at 2020/03/17 17:01:30" << std::endl;
    }
    if (command == "import")
    {
        std::cout << "import <file>:    update current csv <file> to be used as new dataset" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "user$ import 20200317.csv" << std::endl;
        std::cout << "advisorbot$ OrderBook now loaded with 20200317.csv dataset" << std::endl;
    }
}

void Command::prod(OrderBook orderBook)
{
    std::string output;
    std::vector<std::string> products = orderBook.getKnownProducts();
    for (std::string &prod : products)
    {
        output += (prod + ' ');
    }
    std::cout << output << std::endl;
}

double Command::min(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string timestep, std::string order)
{
    std::vector<OrderBookEntry> entries = orderBook.getOrders(arg1, arg2, timestep);

    double min = orderBook.getLowPrice(entries);
    std::cout << "The min " << order << " for " << arg1 << " is " << min << std::endl;
    return min;
}

double Command::max(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string timestep, std::string order)
{
    std::vector<OrderBookEntry> entries = orderBook.getOrders(arg1, arg2, timestep);

    double max = orderBook.getHighPrice(entries);
    std::cout << "The max " << order << " for " << arg1 << " is " << max << std::endl;
    return max;
}

void Command::avg(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string arg3, std::string timestep, std::string order)
{
    std::vector<std::string> timestamps = orderBook.getKnownTimestamps();
    int ts_index;
    for (int i = 0; i < timestamps.size(); i++)
    {
        if (timestamps[i] == timestep)
        {
            ts_index = i;
        }
    }

    int newArg3 = stoi(arg3);
    ts_index = ts_index - newArg3 + 1;
    std::string newTimestep = timestamps[ts_index];
    double sum{};
    int count{};

    for (int i = 0; i < newArg3; i++)
    {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(arg1, arg2, newTimestep);
        for (OrderBookEntry &e : entries)
        {
            sum += e.price;
            count += 1;
        }
        newTimestep = orderBook.getNextTime(newTimestep);
    }
    double avg{sum / count};
    std::cout << "The average " << arg1 << " " << order << " price over the last " << arg3 << " timesteps was " << avg << std::endl;
}

void Command::predict(OrderBook orderBook, std::string arg1, OrderBookType arg2, std::string arg3, std::string timestep, std::string order)
{
    // Simple Moving Average prediction
    // Predict min/max for specific product's ask/bid price
    // Use all previous timesteps min/max averages to find next time step SMA
    // 12 timesteps == 1 min
    // 120 timesteps == 10 min
    // 360 timesteps == 30 min
    // 720 timesteps == 1 hr
    // 1440 timesteps == 2 hr
    // 2160 timesteps == 3 hr
    // 2147 timesteps total
    // each index of timestamps == about 476 orderbook rows

    std::vector<std::string> timestamps = orderBook.getKnownTimestamps();
    int ts_index;
    for (int i = 0; i < timestamps.size(); i++)
    {
        if (timestamps[i] == timestep)
        {
            ts_index = i;
        }
    }

    std::vector<double> m_values;

    // for each timestamp in timestamps[i] calculate average of min/max over multiple intervals (1 min, 10 min, 30 min)

    for (int i = 0; i <= ts_index; i++)
    {
        if (arg1 == "min")
        {
            m_values.push_back(min(orderBook, arg3, arg2, timestamps[i], order));
        }
        if (arg1 == "max")
        {
            m_values.push_back(max(orderBook, arg3, arg2, timestamps[i], order));
        }
    }

    std::vector<double> min_avgs;
    std::vector<double> ten_avgs;
    std::vector<double> thirty_avgs;
    double min_sum{};
    int min_count{};
    double ten_sum{};
    int ten_count{};
    double thirty_sum{};
    int thirty_count{};

    for (int i = 0; i < m_values.size(); i++)
    {
        // 1 min
        if (min_count == 12)
        {
            min_avgs.push_back(min_sum / min_count);
            min_sum = 0.0;
            min_count = 0;
        }
        min_sum += m_values[i];
        min_count += 1;

        // 10 min
        if (ten_count == 120)
        {
            ten_avgs.push_back(ten_sum / ten_count);
            ten_sum = 0.0;
            ten_count = 0;
        }
        ten_sum += m_values[i];
        ten_count += 1;

        // 30 min
        if (thirty_count == 360)
        {
            thirty_avgs.push_back(thirty_sum / thirty_count);
            thirty_sum = 0.0;
            thirty_count = 0;
        }
        thirty_sum += m_values[i];
        thirty_count += 1;
    }

    double minuteTotal;
    for (int i = 0; i < min_avgs.size(); i++)
    {
        minuteTotal += min_avgs[i];
    }
    double minuteSMA = minuteTotal / min_avgs.size();

    double tenTotal;
    for (int i = 0; i < ten_avgs.size(); i++)
    {
        tenTotal += ten_avgs[i];
    }
    double tenSMA = tenTotal / ten_avgs.size();

    double thirtyTotal;
    for (int i = 0; i < thirty_avgs.size(); i++)
    {
        thirtyTotal += thirty_avgs[i];
    }
    double thirtySMA = thirtyTotal / thirty_avgs.size();

    std::cout << "The simple moving average (SMA) for the " << arg1 << " prices of " << arg3 << std::endl;
    std::cout << "The 1 minute SMA is " << minuteSMA << std::endl;
    std::cout << "The 10 minute SMA is " << tenSMA << std::endl;
    std::cout << "The 30 minute SMA is " << thirtySMA << std::endl;
}

void Command::time(std::string timestep)
{
    std::cout << timestep << std::endl;
}

std::string Command::step(OrderBook orderBook, std::string timestep)
{
    std::string newTimestep = orderBook.getNextTime(timestep);
    std::cout << "Now at " << newTimestep << std::endl;
    return newTimestep;
}

OrderBook Command::import(std::string filename)
{
    OrderBook orderBook{filename};
    std::cout << "OrderBook now loaded with " << filename << " dataset" << std::endl;
    return orderBook;
}