package wc;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class ReduceForwc extends Reducer<Text, IntWritable, Text, IntWritable>
{
	public void reduce(Text item, Iterable<IntWritable> value, Context con) throws IOException, InterruptedException
	{
		int sum=0;
		
		for(IntWritable val : value)
		{
			sum = sum + val.get();
		}
		con.write(item, new IntWritable(sum));
	}
}
