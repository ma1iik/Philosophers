
# Philosophers

## Description
The Philosophers project simulates the classic "Dining Philosophers" problem. This problem involves a number of philosophers who alternate between thinking, eating, and sleeping. The challenge is managing shared resources (forks) so that philosophers don’t starve, taking care to avoid data races.

This project was designed to help students learn the basics of multithreading, mutexes, and process synchronization.

## Features
- **Multithreaded Philosopher Simulation**: Each philosopher runs in a separate thread or process.
- **Resource Sharing**: Each philosopher must acquire two forks to eat, simulating resource sharing among concurrent processes.
- **Thread Safety with Mutexes**: Prevents simultaneous access to forks using mutexes.
- **Time Management**: Each philosopher has designated times for eating, thinking, and sleeping.

## Compilation and Usage
Compile the project using the Makefile included. The executable `philo` is generated for the mandatory part, and `philo_bonus` for the bonus.

### Compile
To compile, simply run:
```bash
make
```

### Run
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
**Arguments**:
1. `number_of_philosophers`: Total number of philosophers and forks.
2. `time_to_die`: Time (in ms) before a philosopher dies if they don't start eating.
3. `time_to_eat`: Time (in ms) a philosopher takes to eat.
4. `time_to_sleep`: Time (in ms) a philosopher takes to sleep.
5. `number_of_times_each_philosopher_must_eat` (optional): Simulation stops if each philosopher eats this many times.

## Project Structure
- **`philo/`**: Contains mandatory project source code.
- **`philo_bonus/`**: Contains the bonus part implementation with additional requirements.

## Example
```bash
./philo 5 800 200 200
```

## Simulation Output
Logs each state change of a philosopher in the format:
```
<timestamp> <philosopher_number> has taken a fork
<timestamp> <philosopher_number> is eating
<timestamp> <philosopher_number> is sleeping
<timestamp> <philosopher_number> is thinking
<timestamp> <philosopher_number> died
```

## Gameplay GIF
![Gameplay](path/to/your-gif.gif)

*(Replace `path/to/your-gif.gif` with the actual path to your GIF file in the project.)*

## Author
Developed by [Malik](https://github.com/ma1iik) as part of the 42 School curriculum.
