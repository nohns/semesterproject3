/** @format */

import { useQuery, useQueryClient } from "@tanstack/react-query";

import http from "../../axios";

const getUpdate = async () => {
  const response = await http.get(`v1/updates/`);

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useUpdate = () => {
  const queryClient = useQueryClient();

  const query = useQuery({
    queryKey: ["getUpdate"],
    queryFn: () => getUpdate(),
    retryDelay: 5000,
    retry: true,
    onSuccess: () => {
      queryClient.invalidateQueries(["getDrinks", "getContainers"]);
    },
  });

  return query;
};

export default useUpdate;
