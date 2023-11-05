/** @format */

import ENV from "@/constants/env";

import { useQuery, useQueryClient } from "@tanstack/react-query";

import { http } from "@/api/axios";

if (ENV.MOCKED) {
  await import("./getDrinks.mock.ts");
}

const getUpdate = async () => {
  const response = await http.get(`v1/updates`);

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
      //TODO: Verify if this works
      queryClient.invalidateQueries(["getDrinks", "getFluids"]);
      //Potentially add refetch interval within the use hook itself
    },
  });

  return query;
};

export default useUpdate;
