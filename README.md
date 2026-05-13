# Nyayo House Queue Management System

A C-based simulation system designed to improve public service delivery at Nyayo House, Nairobi, using **Queue** and **Priority Queue** data structures.


## Project Overview

Nyayo House is one of Kenya’s busiest government service centers, handling services such as:

- Passport applications
- Passport collection
- Immigration services
- Government documentation processes

Due to the high number of citizens seeking services daily, challenges such as long queues, overcrowding, poor coordination, and unfair service ordering are common.

This project provides a **queue-based management solution** that organizes customers efficiently using FIFO queues and multiple priority queues.


## Objectives

### Main Objective
To design and implement a queue management system that improves fairness, efficiency, and service delivery at Nyayo House.

### Specific Objectives
- Simulate real-world queue operations using FIFO queues
- Implement priority handling for vulnerable groups
- Track customer waiting times using timestamps
- Provide queue statistics for planning and monitoring
- Demonstrate practical applications of data structures in public systems


## Features

- Add normal customers
- Add priority customers
- Serve customers based on priority hierarchy
- Search for customers
- Remove customers from queues
- Display all queues
- Estimate waiting times
- Generate queue statistics
- Real-time queue simulation


## Data Structures Used

### 1. Normal Queue (FIFO)
Handles regular customers on a first-come-first-served basis.

### 2. Priority Queues
Special groups are handled using separate priority queues:

1. Emergency Cases
2. Diplomatic / VIP
3. Persons With Disabilities (PWD)
4. Elderly Citizens (60+)
5. Expectant Mothers

### Priority Order
Customers are served in the following order:

```text
Emergency → VIP → PWD → Elderly → Expectant Mothers → Normal Queue
