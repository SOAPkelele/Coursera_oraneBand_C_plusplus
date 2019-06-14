void deleteZeros(TasksInfo& info) {
	if (info[TaskStatus::NEW] == 0) {
		info.erase(TaskStatus::NEW);
	}
	if (info[TaskStatus::IN_PROGRESS] == 0) {
		info.erase(TaskStatus::IN_PROGRESS);
	}
	if (info[TaskStatus::TESTING] == 0) {
		info.erase(TaskStatus::TESTING);
	}
	if (info[TaskStatus::DONE] == 0) {
		info.erase(TaskStatus::DONE);
	}
}

class TeamTasks {
public:
	// ѕолучить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return developers.at(person);
	}

	// ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
	void AddNewTask(const string& person) {
		developers[person][TaskStatus::NEW] += 1;
	}

	// ќбновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		TasksInfo untouched;
		if (developers.count(person) > 0) {
			untouched = developers.at(person);
		}
		TasksInfo updated;
		untouched[TaskStatus::DONE] = 0;

		if (untouched[TaskStatus::NEW]) {
			if (untouched[TaskStatus::NEW] - task_count >= 0) {
				updated[TaskStatus::IN_PROGRESS] += task_count;
				untouched[TaskStatus::NEW] -= task_count;
				task_count = 0;
			}
			else {
				task_count -= untouched[TaskStatus::NEW];
				updated[TaskStatus::IN_PROGRESS] += untouched[TaskStatus::NEW];
				untouched.erase(TaskStatus::NEW);
			}
		}


		if (task_count && untouched[TaskStatus::IN_PROGRESS]) {
			if (untouched[TaskStatus::IN_PROGRESS] - task_count >= 0) {
				updated[TaskStatus::TESTING] += task_count;
				untouched[TaskStatus::IN_PROGRESS] -= task_count;
				task_count = 0;
			}
			else {
				task_count -= untouched[TaskStatus::IN_PROGRESS];
				updated[TaskStatus::TESTING] += untouched[TaskStatus::IN_PROGRESS];
				untouched.erase(TaskStatus::IN_PROGRESS);
			}
		}

		if (task_count &&  untouched[TaskStatus::TESTING]) {
			if (untouched[TaskStatus::TESTING] - task_count >= 0) {
				updated[TaskStatus::DONE] += task_count;
				untouched[TaskStatus::TESTING] -= task_count;
				task_count = 0;
			}
			else {
				task_count -= untouched[TaskStatus::TESTING];
				updated[TaskStatus::DONE] += untouched[TaskStatus::TESTING];
				untouched.erase(TaskStatus::TESTING);
			}
		}

		if (developers.count(person) > 0) {
			developers.at(person)[TaskStatus::NEW] = untouched[TaskStatus::NEW] + updated[TaskStatus::NEW];

			developers.at(person)[TaskStatus::IN_PROGRESS] = untouched[TaskStatus::IN_PROGRESS] + updated[TaskStatus::IN_PROGRESS];
			developers.at(person)[TaskStatus::TESTING] = untouched[TaskStatus::TESTING] + updated[TaskStatus::TESTING];
			developers.at(person)[TaskStatus::DONE] += updated[TaskStatus::DONE];//+ untouched[TaskStatus::DONE];
			deleteZeros(developers.at(person));
		}

		deleteZeros(updated);
		deleteZeros(untouched);


		return tie(updated, untouched);
	}

private:
	map < string, TasksInfo > developers;
};