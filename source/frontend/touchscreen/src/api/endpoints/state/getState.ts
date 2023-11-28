/** @format */

import { useQuery, useQueryClient } from "@tanstack/react-query";

import http from "../../axios";
import { useState } from "react";

const getState = async () => {
  const response = await http.get(`v1/state/`);

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data as {
    last_update: number;
    out_of_order: boolean;
    out_of_order_message: string;
    out_of_order_reason: number;
  };
};

const useGetState = () => {
  const queryClient = useQueryClient();
  const [lastUpdate, setLastUpdate] = useState(0);

  const query = useQuery({
    queryKey: ["getState"],
    queryFn: () => getState(),
    refetchInterval: 2000,
    //staleTime: 5000,
    retry: true,
    onSuccess: (data) => {
      // Update app state
      if (lastUpdate < data.last_update) {
        queryClient.invalidateQueries(["getDrinks", "getContainers"]);
        // Update last time we updated
        setLastUpdate(data.last_update);
      }
    },
  });

  return query;
};

export default useGetState;
