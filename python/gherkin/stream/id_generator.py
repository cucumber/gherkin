class IdGenerator:
    def __init__(self) -> None:
        self._id_counter = 0

    def get_next_id(self) -> str:
        id = self._id_counter
        self._id_counter += 1
        return str(id)
